#ifndef CLASSHEAP_HPP_
#define CLASSHEAP_HPP_

#include <map>
#include <cstring>

#include "classLoader.hpp"
#include "classFile.hpp"

class ClassHeap{
	private:
		std::map<std::string, ClassFile *> classHeap;
		ClassLoader 					 classLoader;
	public:
		ClassFile * getClass(std::string className);
};

#endif /* CLASSHEAP_HPP_ */