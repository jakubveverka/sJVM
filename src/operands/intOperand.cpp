
#include "../../include/operands/intOperand.hpp"

	 IntOperand::IntOperand(int val) : value(val)
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
