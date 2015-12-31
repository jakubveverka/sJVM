#ifndef OBJECTTABLE_HPP_
#define OBJECTTABLE_HPP_

#include <string>

class Ref;
class ClassFile;

class ObjectTable{
	private:

	public:
		int 		 tableSize = 100;
	 	Ref 	  ** objectTable;

	public:
			 ObjectTable();
		int addHeapObjectRef(int freeSpaceIndex, ClassFile * javaClass);
		int addHeapArrayRef(int freeSpaceIndex, char arrayType);
		int addHeapObjectArrayRef(int freeSpaceIndex, std::string className);
		int findFreeIndex();
		ClassFile * getClassRef(int index);
		int 		getHeapIndex(int index);
};

#endif /* OBJECTTABLE_HPP_ */
