#include <iostream>

#include "../include/classFile.hpp"

int main(int argc, char * argv[]){

	if(argc < 2){
		std::cout << "Missing classfile name!";
		return 1;
	}
	
	ClassFile classfile;

	classfile.

	StackFrame stackFrame = new StackFrame();
	ClassStorage classStorage = new ClassStorage();

	Frame initFrame = new Frame("main", argv[1], stackFrame, classStorage);
	
	std::cout << "Done: " << ret << std::endl;
	return 0;
}


