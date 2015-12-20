#ifndef CLASSLOADER_HPP_
#define CLASSLOADER_HPP_

#include "classFile.hpp"

class ClassLoader{
	private:

	public:
		ClassFile * loadClass(std::string className);
};

#endif /* CLASSLOADER_HPP_ */