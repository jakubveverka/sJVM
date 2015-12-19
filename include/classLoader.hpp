#ifndef CLASSLOADER_HPP_
#define CLASSLOADER_HPP_

class ClassLoader{
	private:

	public:
		ClassFile * loadClass(std::string className);
};

#endif /* CLASSLOADER_HPP_ */