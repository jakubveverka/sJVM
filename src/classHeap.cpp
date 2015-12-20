
#include "../include/classHeap.hpp"
#include "../include/classLoader.hpp"
#include "../include/classFile.hpp"

ClassFile * ClassHeap::getClass(std::string className)
{
	std::map<std::string, ClassFile *>::iterator it;
	it = classHeap.find(className);
	if(it == classHeap.end())
	{
		classHeap . insert( std::pair<std::string, ClassFile *>(className, classLoader.loadClass(className) ) );
	}
	return classHeap[className];
}