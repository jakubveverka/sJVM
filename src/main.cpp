#include <iostream>
#include <stack>

#include "../include/classFile.hpp"
#include "../include/classHeap.hpp"
#include "../include/frame.hpp"
#include "../include/stackFrame.hpp"
#include "../include/executionUnit.hpp"
#include "../include/objectHeap.hpp"
#include "../include/objectTable.hpp"
#include "../include/garbageCollector.hpp"

int main(int argc, char * argv[]){

	if(argc < 2){
		std::cout << "Missing classfile name!";
		return 1;
	}

	std::stack<Frame*> stackFrame;
	ClassHeap  * classHeap = new ClassHeap();
	ObjectTable * objectTable = new ObjectTable();
	ObjectHeap * objectHeap = new ObjectHeap(classHeap, objectTable);
	GarbageCollector * garbageCollector = new GarbageCollector(objectHeap, objectTable, &stackFrame);
	objectTable->setGarbageCollector(garbageCollector);
	objectHeap->setGarbageCollector(garbageCollector);


	classHeap -> getClass("test/java/lang/Object");
	classHeap -> getClass("test/java/lang/String");
	classHeap -> getClass("test/java/io/PrintStream");

	Frame * initFrame = new Frame("main","([Ljava/lang/String;)V", argv[1], &stackFrame, classHeap);
	stackFrame.push(initFrame);

	ExecutionUnit * ex = new ExecutionUnit(&stackFrame, objectHeap);

	Frame * frame = stackFrame.top();

	try {
		ex -> execute(frame);
	} catch(int e) {
		if(e == 21) std::cout << "Out of memory exception" << std::endl;
		else std::cout << "Exception " << e << " occured" << std::endl;
		return 1;
	}

	std::cout << "Done: " << std::endl;
	return 0;
}
