
#include "../include/objectArrayRef.hpp"

ObjectArrayRef::ObjectArrayRef(int p_index, std::string p_className) : Ref(p_index), className(p_className)
{

}

int ObjectArrayRef::getIndex() const
{
	return heapIndex;
}


