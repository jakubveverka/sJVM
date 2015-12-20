
#include <iostream>

#include "../include/classLoader.hpp"

ClassFile * ClassLoader::loadClass(std::string className)
{
	ClassFile * classfile = new ClassFile();
	std::cout << "Loading class: " << className << std::endl;
	classfile -> loadClass(className);
	return classfile;  
}