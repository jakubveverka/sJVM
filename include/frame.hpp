#ifndef FRAME_HPP_
#define FRAME_HPP_

class Frame{

public:
	Frame(method_info_w_code p_method, );
private:
	Operand 		  * localVariables;
	OperandStack 		stack;
	JavaClass 			javaClass;
	method_info_w_code 	method;
	int 				pc;
};

#endif /* FRAME_HPP_ */