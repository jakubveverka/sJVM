#ifndef EXECUTIONUNIT_HPP_
#define EXECUTIONUNIT_HPP_

#include <stack>

#include "frame.hpp"

class ObjectHeap;

class ExecutionUnit{
	private:
		std::stack<Frame*>* frameStack;
		ObjectHeap       * objectHeap;
	public:
			 ExecutionUnit(std::stack<Frame*>* p_frameStack, ObjectHeap * objectHeap);
		void execute(Frame *);
		void executeInvoke(Frame *, u1 type);
		int  executeNew(Frame *);
		int  executeNewArray(Frame *);
		u2	 getNumberOfMethodParams(std::string p_description);
		void putfield(Frame * frame);
		void getField(Frame * frame);
		int  loadConstant(Frame * frame);
		void executeNativeMethod(Frame * frame);


};

#endif /* EXECUTIONUNIT_HPP_ */
