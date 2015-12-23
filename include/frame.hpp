#ifndef FRAME_HPP_
#define FRAME_HPP_

#include <vector>
#include <stack>

#include "operandStack.hpp"
#include "classFile.hpp"
#include "classHeap.hpp"
#include "operands/intOperand.hpp"

class StackFrame;

class Frame{

	private:
		std::vector<Operand*>  localVariables;
		std::stack<Operand*>   opStack;
		ClassFile 			 * javaClass;
		method_info_w_code 	   method;
		int 				   pc;
		ClassHeap			 * classHeap;
		std::stack<Frame*>	   stackFrame;

	public:
		Frame(std::string p_methodName, std::string p_className, std::stack<Frame*> p_stackFrame, ClassHeap * p_classHeap );
		method_info_w_code getMethod();
		int				   getPc();
		void 			   pushOperand(Operand *op);
		void 			   movePc(int steps);
		void			   storeOperand(int index, Operand *op);
		Operand			 * loadOperand(int index);
		Operand			 * topPopOperand();
		void 				printOpStack();
};

#endif /* FRAME_HPP_ */
