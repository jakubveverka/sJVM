#ifndef OBJECTTABLE_HPP_
#define OBJECTTABLE_HPP_

#include <cstdlib>

class Ref;
class ClassFile;
class GarbageCollector;

class ObjectTable{
	private:

	public:
		int 		 tableSize = 100;
	 	Ref 	  ** objectTable;
		GarbageCollector * garbageCollector = NULL;

	public:
			 ObjectTable();
		int addHeapObjectRef(int freeSpaceIndex, ClassFile * javaClass);
		int addHeapArrayRef(int freeSpaceIndex, char arrayType);
		int findFreeIndex();
		ClassFile * getClassRef(int index);
		int 		getHeapIndex(int index);
		void    setGarbageCollector(GarbageCollector* pGarbageCollector);
		Ref* getRef(int index);
		void 	  print();
};

#endif /* OBJECTTABLE_HPP_ */
