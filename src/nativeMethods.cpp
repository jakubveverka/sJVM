
#include <iostream>

#include "../include/nativeMethods.hpp"
#include "../include/frame.hpp"
#include "../include/objectHeap.hpp"
#include "../include/operands/operand.hpp"

void void_PrintStream_Print_String(Frame * frame, ObjectHeap * objectHeap)
{
	Operand * refOp = frame -> localVariables[0];

	Operand * valueOp = objectHeap -> getObjectValue(refOp, "value");

	std::cout << valueOp -> getStringValue() << std::endl;
}