#include <iostream>

#include "../include/frame.hpp"


	Frame::Frame(std::string p_methodName, std::string p_methodDescription, std::string p_className, std::stack<Frame*> p_stackFrame, ClassHeap * p_classHeap )
{

	classHeap = p_classHeap;
	javaClass = classHeap -> getClass(p_className + ".class");
	method    = javaClass -> getMethod(p_methodName, p_methodDescription);
	stackFrame = p_stackFrame;
	localVariables.reserve(method . code_attr -> max_locals);
	pc = 0;
}

method_info_w_code Frame::getMethod(){
	return method;
}

int				   Frame::getPc()
{
	return pc;
}

void Frame::pushOperand(Operand *op)
{
	opStack.push(op);
	std::cout << opStack . size() << std::endl;
}

void Frame::movePc(int steps)
{
	pc += steps;
}

void Frame::storeOperand(int index, Operand *op)
{
	localVariables[index] = op;
}

Operand * Frame::loadOperand(int index)
{
	return localVariables[index];
}

Operand * Frame::topPopOperand()
{
	Operand * tmp = opStack.top();
	opStack.pop();
	std::cout << opStack . size() << std::endl;
	return tmp;
}
