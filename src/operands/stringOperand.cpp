
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

	  	StringOperand::~StringOperand()
{

}	
