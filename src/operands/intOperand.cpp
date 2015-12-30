
#include "../../include/operands/intOperand.hpp"

	 IntOperand::IntOperand(int val) : value(val)
{

}
	IntOperand::~IntOperand()
{

}

int IntOperand::getValue() const
{
	return value;
}

void IntOperand::setValue(int val)
{
	value = val;
}

Operand* IntOperand::clone()
{
	Operand* clonedOperand = new IntOperand(value);
	return clonedOperand;
}
