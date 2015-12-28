#ifndef CLASSLOADER_HPP_
#define CLASSLOADER_HPP_

#include "classFile.hpp"

class ClassLoader{
	private:

	public:
		ClassFile * loadClass(std::string className, ClassHeap * classHeap);
};

#endif /* CLASSLOADER_HPP_ */