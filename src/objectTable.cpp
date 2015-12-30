
#include "../include/objectTable.hpp"
#include "../include/objectRef.hpp"
#include "../include/arrayRef.hpp"
#include "../include/garbageCollector.hpp"
#include "../include/debugMsg.hpp"

	ObjectTable::ObjectTable()
{
	objectTable = new Ref*[tableSize];
}

int ObjectTable::addHeapObjectRef(int freeSpaceIndex, ClassFile * javaClass)
{
	int freeTableIndex = findFreeIndex();
	objectTable[freeTableIndex] = new ObjectRef(freeSpaceIndex, javaClass);
	return freeTableIndex;
}

int ObjectTable::addHeapArrayRef(int freeSpaceIndex, char arrayType)
{
	int freeTableIndex = findFreeIndex();
	objectTable[freeTableIndex] = new ArrayRef(freeSpaceIndex, arrayType);
	return freeTableIndex;
}

int ObjectTable::findFreeIndex(){
	for(int j = 0; j < 2; j++) {
		for (int i = 0; i < tableSize; i++)
		{
			if(objectTable[i] == nullptr)
				return i;
		}
		if(j == 0 && garbageCollector != NULL) garbageCollector->execute();
		else throw 21;
	}
	throw 21;
}

ClassFile * ObjectTable::getClassRef(int index)
{
	return dynamic_cast<ObjectRef*>(objectTable[index]) -> classFile;
}

int ObjectTable::getHeapIndex(int index)
{
	return objectTable[index] -> heapIndex;
}

void    ObjectTable::setGarbageCollector(GarbageCollector* pGarbageCollector)
{
	garbageCollector = pGarbageCollector;
}

Ref* ObjectTable::getRef(int index) {
	return objectTable[index];
}

void ObjectTable::print()
{
	DEBUG_MSG("Printing object table:");
	for(int i = 0; i < tableSize; i++) {
		if(objectTable[i] == nullptr) DEBUG_MSG(std::to_string(i) + ". position is free");
		else if(ObjectRef* o = dynamic_cast<ObjectRef*>(objectTable[i])) DEBUG_MSG(std::to_string(i) + ". position is ObjectRef with index " + std::to_string(o->getIndex()));
		else if(ArrayRef* a = dynamic_cast<ArrayRef*>(objectTable[i])) DEBUG_MSG(std::to_string(i) + ". position is ArrayRef with index " + std::to_string(a->getIndex()));
		else DEBUG_MSG(std::to_string(i) + ". position unknown operand");
	}
	DEBUG_MSG("Finished printing object table");
}
