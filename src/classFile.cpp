#include <fstream>
#include <iostream>

#include "../include/classFile.hpp"
#include "../include/definitions.hpp"

int ClassFile::loadClass(char * classFileName)
{

	std::ifstream file;
	int length;
	char * p;

	std::cout << classFileName << "wtf" << std::endl;

	file.open(classFileName);

	if(file.is_open())
	{
		file.seekg(0,std::ios::end);
		length = file.tellg();
		file.seekg(0, std::ios::beg);
		p = new char[length];
		file.read(p, length); 
		file.close();
	} 
	else 
	{
		std::cout << "File load failed!" << std::endl;
		return 1;
	}
	magic = getu4(p); p += 4;

	if(magic != 0xCAFEBABE)
	{
		std::cout << "Magic constant is not right!:" << std::endl;
		return 1;
	}

	minor_version = 			getu2(p); p += 2;
	major_version = 			getu2(p); p += 2;
	constant_pool_count = getu2(p); p += 2;
	if(constant_pool_count > 0)
	{
		loadConstants(p);
	}
	access_flags = 				getu2(p); p += 2;
	this_class = 					getu2(p); p += 2;
	super_class = 				getu2(p); p += 2;
	interfaces_count = 		getu2(p); p += 2;
	if(interfaces_count > 0)
	{
		loadInterfaces(p);
	}
	fields_count = 				getu2(p); p += 2;
	if(fields_count > 0)
	{
		loadFields(p);
	}
	/* 
	* fields; //[fields_count]
	methods_count;
	*	methods; //[methods_count]
	attributes_count;
	* attributes; //[attributes_count]
*/

 
	return 0;
}

int ClassFile::loadConstants(char * &p)
{
	constant_pool = new cp_info*[constant_pool_count - 1];
	for (int i = 0; i < constant_pool_count; ++i)
	{
		// Set the bytecode actual pointer here. 
		// Need to be type casted to cp_info pointer
		constant_pool[i] = (cp_info*)p;

		// Get the size the constant size and move pointer by that
		int constSize = getConstantSize(p);
		p += constSize;

		// long and double constant takes up two entries in constant pool
		if(constant_pool[i] -> tag == CONSTANT_Long || constant_pool[i] -> tag == CONSTANT_Double)
		{
			constant_pool[i + 1] = NULL;
			i++;
		}
	}
	return 0;
}

int ClassFile::getConstantSize(char * &p)
{
	// read the tag of cp_info (first byte)
	u1 tag = getu1(p);

	// return the size of the constant based on its structure size
	switch (tag)
	{
		case CONSTANT_Class:
				return 3;
		case CONSTANT_Fieldref:
				return 5;
		case CONSTANT_Methodref:
				return 5;
		case CONSTANT_InterfaceMethodref:
				return 5;
		case CONSTANT_String:
				return 3;
		case CONSTANT_Integer:
				return 5;
		case CONSTANT_Float:
				return 5;
		case CONSTANT_Long:
				return 9;
		case CONSTANT_Double:
				return 9;
		case CONSTANT_NameAndType:
				return 5;
		case CONSTANT_Utf8:
				return 3 + getu2(p + 1); // we need to get the size of "bytes" parameter in this constant
		case CONSTANT_MethodHandle:
				return 4;
		case CONSTANT_MethodType:
				return 3;
		case CONSTANT_InvokeDynamic:
				return 5;
		default:
				break;
	}
	return 0;
}

int ClassFile::loadInterfaces(char * &p)
{
	interfaces = new u2[interfaces_count];
	for (int i = 0; i < interfaces_count; ++i)
	{
		interfaces[i] = getu2(p); p += 2;
	}
	return 0;
}

int ClassFile::loadFields(char * &p)
{

	return 0;
}