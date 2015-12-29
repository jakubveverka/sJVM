
#include <iostream>

#include "../include/classLoader.hpp"

ClassFile * ClassLoader::loadClass(std::string className, ClassHeap * classHeap)
{
	ClassFile * classfile = new ClassFile(classHeap);
	std::cout << "Loading class: " << className << std::endl;
	classfile -> loadClass(className + ".class");
	std::cout << "Loaded: " << classfile -> getName() << std::endl;
	return classfile;  
}