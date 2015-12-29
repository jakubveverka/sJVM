

#include "../include/objectHeap.hpp"
#include "../include/classFile.hpp"
#include "../include/classHeap.hpp"
#include "../include/operands/operand.hpp"
#include "../include/operands/intOperand.hpp"
#include "../include/operands/stringOperand.hpp"
#include "../include/objectTable.hpp"

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
	int freeSpaceIndex = getFreeSpace(length);

	for (int i = freeSpaceIndex; i < freeSpaceIndex + length; i++)
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
	int i = 0;
	while(1){
		while(data[i] != nullptr){		
			i++;
			if(i > heapSize - 1) 
				return -1;
		}
		bool free = true;
		for (int j = 0; j < objectSize; j++)
		{	
			if(i + j > heapSize - 1)
				return -1;
			if(data[i + j] != nullptr) 
				free = false;
		}
		if(free)
			return i;
	}
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
	ClassFile * javaClass = objectTable -> getClassRef(refOp -> getValue());

	int fieldIndex = javaClass -> getFieldIndex(fieldName);

	return data[objectTable -> getHeapIndex(refOp -> getValue()) + fieldIndex];
}

Operand * ObjectHeap::loadArrayOp(Operand * refOp, Operand * indexOp)
{
	return data[objectTable -> getHeapIndex(refOp -> getValue()) + indexOp -> getValue()];
}

void	  ObjectHeap::storeArrayOp(Operand * refOp, Operand * indexOp, Operand * value)
{
	data[objectTable -> getHeapIndex(refOp -> getValue()) + indexOp -> getValue()] = value;
}

int	 	  ObjectHeap::createString(std::string stringValue)
{
	ClassFile * javaClass = classHeap -> getClass("java/lang/String");
	
	int freeSpaceIndex = getFreeSpace(1);

	data[freeSpaceIndex] = new StringOperand(stringValue);

	return objectTable -> addHeapObjectRef(freeSpaceIndex, javaClass);
}
