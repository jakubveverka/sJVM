#include <iostream>

#include <iostream>

#include "../include/frame.hpp"
#include "../include/debugMsg.hpp"


	Frame::Frame(std::string p_methodName, std::string p_methodDescription, std::string p_className, std::stack<Frame*>* p_stackFrame, ClassHeap * p_classHeap )
{

	classHeap = p_classHeap;
	javaClass = classHeap -> getClass(p_className);
	method    = javaClass -> getMethod(p_methodName, p_methodDescription);
	javaClass = javaClass -> setClassByMethod(p_methodName, p_methodDescription);
	stackFrame = p_stackFrame;
	if(method . access_flags & ACC_NATIVE )
	{
		localVariables.reserve(5);
		localVariablesSize = 5;
	}
	else{
		localVariables.reserve(method . code_attr -> max_locals);
		localVariablesSize = method . code_attr -> max_locals;
	}

	for(int i = 0; i < localVariablesSize; i++) localVariables[i] = nullptr;

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
	return tmp;
}

void Frame::printOpStack()
{
	DEBUG_MSG("printing opStack:");
	for (std::stack<Operand *> stackCopy = opStack; !stackCopy.empty(); stackCopy.pop()) {
        DEBUG_MSG(stackCopy.top()->getValue());
	}
	DEBUG_MSG("end of printing");
}

std::stack<Operand*>* Frame::getOpStack()
{
	return &opStack;
}
