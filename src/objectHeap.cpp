

#include "../include/objectHeap.hpp"
#include "../include/classFile.hpp"
#include "../include/classHeap.hpp"
#include "../include/operands/operand.hpp"
#include "../include/operands/intOperand.hpp"
#include "../include/operands/stringOperand.hpp"
#include "../include/operands/refOperand.hpp"
#include "../include/objectTable.hpp"
#include "../include/garbageCollector.hpp"

	ObjectHeap::ObjectHeap(ClassHeap * pClassHeap, ObjectTable * pObjectTable) : classHeap(pClassHeap), objectTable(pObjectTable)
{
	data = new Operand*[heapSize];
	for (int i = 0; i < heapSize; i++)
	{
		data[i] = nullptr;
	}
}

int ObjectHeap::createObject(std::string className)
{
	ClassFile * javaClass = classHeap -> getClass(className);

	int objectSize	= javaClass -> getObjectSize();

	int freeSpaceIndex = getFreeSpace(objectSize);

	for (int i = freeSpaceIndex; i < freeSpaceIndex + objectSize; i++)
	{
		data[i] = new Operand();
	}

	return objectTable -> addHeapObjectRef(freeSpaceIndex, javaClass);

}

int	ObjectHeap::createArray(int length, char arrayType)
{
	int freeSpaceIndex = getFreeSpace(length + 1);

	data[freeSpaceIndex] = new IntOperand(length);
	for (int i = freeSpaceIndex + 1; i < freeSpaceIndex + length + 1; i++)
	{
		switch(arrayType){
			case 10:  // int
				data[i] = new IntOperand(0);
				break;
			default:
				data[i] = new Operand();
				break;
		}
	}

	return objectTable -> addHeapArrayRef(freeSpaceIndex, arrayType);
}


int ObjectHeap::getFreeSpace(int objectSize)
{
	for(int j = 0; j < 2; j++) {
		int i = 0;
		int result = -2;
		while(1){
			while(data[i] != nullptr){
				i++;
				if(i > heapSize - 1) {
					result = -1;
					break;
				}
			}
			if(result == -1) break;
			bool free = true;
			for (int j = 0; j < objectSize; j++)
			{
				if(i + j > heapSize - 1) {
					result = -1;
					break;
				}
				if(data[i + j] != nullptr)
					free = false;
			}
			if(result == -1) break;
			if(free)
				return i;
		}
		if( j == 0 && result == -1 && garbageCollector != NULL) garbageCollector->execute();
		else throw 21;
	}
	throw 21;
}

void ObjectHeap::setObjectValue(Operand * refOp, std::string fieldName, Operand * valueOp)
{
	ClassFile * javaClass = objectTable -> getClassRef(refOp -> getValue());

	int fieldIndex = 0;

	fieldIndex += javaClass -> getFieldIndex(fieldName);

	data[objectTable -> getHeapIndex(refOp -> getValue()) + fieldIndex] = valueOp;
}

Operand * ObjectHeap::getObjectValue(Operand * refOp, std::string fieldName)
{
	int index = getFieldHeapIndex(refOp, fieldName);

	return data[index];
}

Operand * ObjectHeap::getArrayLength(Operand * refOp)
{
	return data[objectTable -> getHeapIndex(refOp -> getValue())];
}

Operand * ObjectHeap::loadArrayOp(Operand * refOp, Operand * indexOp)
{
	int index = getArrayOpIndex(refOp, indexOp);
	return data[index];
}

void	  ObjectHeap::storeArrayOp(Operand * refOp, Operand * indexOp, Operand * value)
{
	data[objectTable -> getHeapIndex(refOp -> getValue()) + indexOp -> getValue() + 1] = value;
}

int	 	  ObjectHeap::createString(std::string stringValue)
{
	ClassFile * javaClass = classHeap -> getClass("java/lang/String");

	int freeSpaceIndex = getFreeSpace(1);

	data[freeSpaceIndex] = new StringOperand(stringValue);

	return objectTable -> addHeapObjectRef(freeSpaceIndex, javaClass);
}

void    ObjectHeap::setGarbageCollector(GarbageCollector* pGarbageCollector)
{
	garbageCollector = pGarbageCollector;
}

void ObjectHeap::print()
{
	DEBUG_MSG("Printing object heap:");
	for(int i = 0; i < 15; i++) {
		if(data[i] == nullptr) DEBUG_MSG(std::to_string(i) + ". position is free");
		else if(IntOperand* o = dynamic_cast<IntOperand*>(data[i])) DEBUG_MSG(std::to_string(i) + ". position is IntOperand with value " + std::to_string(o->getValue()));
		else if(RefOperand* o = dynamic_cast<RefOperand*>(data[i])) DEBUG_MSG(std::to_string(i) + ". position is RefOperand with value " + std::to_string(o->getValue()));
		else if(StringOperand* o = dynamic_cast<StringOperand*>(data[i])) DEBUG_MSG(std::to_string(i) + ". position is StringOperand with value " + o->getStringValue());
		else DEBUG_MSG(std::to_string(i) + ". position unknown operand");
	}
	DEBUG_MSG("Finished printing object heap");
}

int ObjectHeap::getFieldHeapIndex(Operand * refOp, std::string fieldName) {
	ClassFile * javaClass = objectTable -> getClassRef(refOp -> getValue());

	int fieldIndex = javaClass -> getFieldIndex(fieldName);

	return objectTable -> getHeapIndex(refOp -> getValue()) + fieldIndex;
}

int ObjectHeap::getArrayOpIndex(Operand * refOp, Operand * indexOp)
{
	return objectTable -> getHeapIndex(refOp -> getValue()) + indexOp -> getValue() + 1;
}
