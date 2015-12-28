
#include "../include/objectRef.hpp"
#include "../include/classFile.hpp"

ObjectRef::ObjectRef(int p_index, ClassFile * p_classFile) : Ref(p_index)
{
	classFile = p_classFile;
}

int ObjectRef::getIndex() const
{
	return heapIndex;
}