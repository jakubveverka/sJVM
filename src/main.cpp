#include <iostream>
#include <stack>

#include "../include/classFile.hpp"
#include "../include/classHeap.hpp"
#include "../include/frame.hpp"
#include "../include/stackFrame.hpp"
#include "../include/executionUnit.hpp"

int main(int argc, char * argv[]){

	if(argc < 2){
		std::cout << "Missing classfile name!";
		return 1;
	}

	std::stack<Frame*> stackFrame;
	ClassHeap  * classHeap = new ClassHeap();

	Frame * initFrame = new Frame("main","([Ljava/lang/String;)V", argv[1], stackFrame, classHeap);
	stackFrame.push(initFrame);

	ExecutionUnit * ex = new ExecutionUnit(stackFrame);

	Frame * frame = stackFrame.top();

	ex -> execute(frame);

	std::cout << "Done: " << std::endl;
	return 0;
}


