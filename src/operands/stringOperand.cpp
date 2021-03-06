
#include "../../include/operands/stringOperand.hpp"

		StringOperand::StringOperand(std::string val) : value(val)
{

}

std::string	StringOperand::getStringValue() const
{
	return value;
}

void 	StringOperand::setStringValue(std::string val)
{
	value = val;
}

Operand* StringOperand::clone()
{
	Operand* clonedOperand = new StringOperand(value);
	return clonedOperand;
}

	  	StringOperand::~StringOperand()
{

}
