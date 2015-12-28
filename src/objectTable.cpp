
#include "../include/objectTable.hpp"
#include "../include/objectRef.hpp"
#include "../include/arrayRef.hpp"

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
	for (int i = 0; i < tableSize; i++)
	{
		if(objectTable[i] == nullptr)
			return i;
	}
	return -1;
}

ClassFile * ObjectTable::getClassRef(int index)
{
	return dynamic_cast<ObjectRef*>(objectTable[index]) -> classFile;
}

int ObjectTable::getHeapIndex(int index)
{
	return objectTable[index] -> heapIndex;
}
