
#include "../../include/operands/operand.hpp"

int  Operand::getValue() const { return 0;}
void Operand::setValue(int val) {}
std::string Operand::getStringValue() const { return "";}
void Operand::setStringValue(std::string val) {}
Operand* Operand::clone() { return NULL; }
