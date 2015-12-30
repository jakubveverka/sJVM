
#include "../include/ref.hpp"

	Ref::Ref(int p_index) : heapIndex(p_index)
{

}

void Ref::setGcNumber(int pGcNumber)
{
	gcNumber = pGcNumber;
}

int  Ref::getGcNumber() {
	return gcNumber;
}
