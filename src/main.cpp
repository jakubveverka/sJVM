#include <iostream>

#include "../include/classFile.hpp"

int main(int argc, char * argv[]){

	ClassFile classfile;

	//std::cout << (char *)argv[2];
	if(argc < 2){
		std::cout << "Missing classfile name!";
		return 1;
	}
	int ret = classfile.loadClass(argv[1]);

	return 0;
}


