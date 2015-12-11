
#include <fstream>
#include <iostream>

#include "../include/classFile.hpp"

int load_class(char * classFileName, ClassFile classfile){

	std::ifstream file;
	int length;
	char * p;

	std::cout << classFileName << "wtf" << std::endl;

	file.open(classFileName);

	if(file.is_open()){
		file.seekg(0,std::ios::end);
		length = file.tellg();
		file.seekg(0, std::ios::beg);
		p = new char[length];
		file.read(p, length);
		file.close();
	} else {
		std::cout << "File load failed!" << std::endl;
	}
	
	return 0;
}
