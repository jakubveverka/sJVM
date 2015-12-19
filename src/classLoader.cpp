
ClassFile * ClassLoader::loadClass(std::string className)
{
	ClassFile * classfile = new ClassFile();
	classfile.loadClass(argv[1]);
	return classfile;
}