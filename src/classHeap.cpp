
#include "../include/classHeap.hpp"
#include "../include/classLoader.hpp"

ClassFile * ClassHeap::getClass(std::string className)
{
	std::map<std::String, ClassFile>::iterator it;
	it = classHeap.find(className);
	if(it == classHeap.end())
	{
		classStorage[className] = classLoader.loadClass(className);
	}
	return classStorage[className];
}