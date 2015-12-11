#include <iostream>

#include "../include/classFile.hpp"
#include "../include/classLoader.hpp"

int main(int argc, char * argv[]){

	ClassFile classfile;

	//std::cout << (char *)argv[2];
	if(argc < 2){
		std::cout << "Missing classfile name!";
		return 1;
	}
	int ret = load_class(argv[1], classfile);

	return 0;
}


