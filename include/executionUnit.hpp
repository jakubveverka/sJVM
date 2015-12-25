#ifndef EXECUTIONUNIT_HPP_
#define EXECUTIONUNIT_HPP_

#include <stack>

#include "frame.hpp"

class ExecutionUnit{
	private:
		std::stack<Frame*> frameStack;
	public:
			 ExecutionUnit(std::stack<Frame*> p_frameStack);
		void execute(Frame *);
		void executeInvoke(Frame *);
		u2	 getNumberOfMethodParams(std::string p_description);

};

#endif /* EXECUTIONUNIT_HPP_ */