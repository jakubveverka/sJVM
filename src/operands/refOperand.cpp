
#include "../../include/operands/refOperand.hpp"

		RefOperand::RefOperand(int i) : index(i)
{

}	

int 	RefOperand::getValue() const
{
	return index;
}

void 	RefOperand::setValue(int i)
{
	index = i;
}

	  	RefOperand::~RefOperand()
{

}	
