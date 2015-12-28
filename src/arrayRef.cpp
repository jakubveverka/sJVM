
#include "../include/arrayRef.hpp"

	ArrayRef::ArrayRef(int p_index, char p_arrayType) : Ref(p_index), arrayType(p_arrayType)
{

}

int ArrayRef::getIndex() const
{
	return heapIndex;
}