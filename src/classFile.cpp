#include <fstream>
#include <iostream>
#include <cstring>

#include "../include/classFile.hpp"
#include "../include/definitions.hpp"

int ClassFile::loadClass(char * classFileName)
{

	std::ifstream file;
	int length;
	char * p;

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

	minor_version 			= getu2(p); p += 2;
	major_version 			=	getu2(p); p += 2;
	constant_pool_count = getu2(p); p += 2;
	if(constant_pool_count > 0)
	{
		loadConstants(p);
	}
	access_flags 				= getu2(p); p += 2;
	this_class 					= getu2(p); p += 2;
	super_class 				= getu2(p); p += 2;
	interfaces_count 		= getu2(p); p += 2;
	if(interfaces_count > 0)
	{
		loadInterfaces(p);
	}
	fields_count 				= getu2(p); p += 2;
	if(fields_count > 0)
	{
		loadFields(p);
	}
	methods_count 			= getu2(p); p += 2;
	if(methods_count > 0)
	{
		loadMethods(p);
	}
	attributes_count 		= getu2(p); p += 2;
	if(attributes_count > 0)
	{
		loadAttributes(p);
	}
	
	return 0;
}

int ClassFile::loadConstants(char * &p)
{
	constant_pool = new cp_info*[constant_pool_count - 1];
	for (int i = 1; i < constant_pool_count; i++)
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
	for (int i = 0; i < interfaces_count; i++)
	{
		interfaces[i] = getu2(p); p += 2;
	}
	return 0;
}

int ClassFile::loadFields(char * &p)
{
	fields = new field_info[fields_count];
	for (int i = 0; i < fields_count; i++)
	{
		fields[i] . access_flags = getu2(p); p += 2;
    fields[i] . name_index = getu2(p); p += 2;
    fields[i] . descriptor_index = getu2(p); p += 2;
    fields[i] . attributes_count = getu2(p); p += 2;
    if(fields[i] . attributes_count > 0 )
    {
    	fields[i] . attributes = new attribute_info[attributes_count];
	    for (int j = 0; j < attributes_count; j++)
	    {
	    	fields[i] . attributes[j] . attribute_name_index = getu2(p); p += 2;
    		fields[i] . attributes[j] . attribute_length     = getu4(p); p += 4;
    		if(fields[i] . attributes[j] . attribute_length > 0)
    		{
    			fields[i] . attributes[j] . info = new u1[fields[i] . attributes[j] . attribute_length];
    			for (unsigned int k = 0; k < fields[i] . attributes[j] . attribute_length; k++)
    			{
    				fields[i] . attributes[j] . info[k] = getu1(p); p += 1;
    			}
    		}
    	}
	  }
	}
	return 0;
}

int ClassFile::getAttrName(u2 attr_name_index, std::string &attr_value)
{
	u1 * pN;

	if(attr_name_index < 1 || attr_name_index > constant_pool_count)
	{
		return 1;
	}
	//pointer to constant in constant pool
	pN = (u1 *)constant_pool[attr_name_index];

	//get length of the string
	int attr_name_length = getu2(pN + 1);
	char * buffer = new char[attr_name_length + 1];
	buffer[attr_name_length] = 0; // end string with 0
	memcpy(buffer, pN + 3, attr_name_length);
	attr_value = std::string(buffer);
	return 0;
}

int ClassFile::loadMethods(char * &p)
{
	methods = new method_info_w_code[methods_count];
	for (int i = 0; i < methods_count; i++)
	{
		methods[i] . access_flags 			= getu2(p); 	p += 2;
	    methods[i] . name_index 				= getu2(p); 	p += 2;
	    methods[i] . descriptor_index 	= getu2(p); 	p += 2;
	    methods[i] . attributes_count 	= getu2(p); 	p += 2;
	    if(methods[i] . attributes_count > 0)
	    {
	    	methods[i] . attributes = new attribute_info[methods[i] . attributes_count];
	    	for (int j = 0; j < methods[i] . attributes_count; j++)
	    	{
	    		methods[i] . attributes[j] . attribute_name_index = getu2(p); p += 2;
	    		methods[i] . attributes[j] . attribute_length 		= getu4(p); p += 4;
	    		if(methods[i] . attributes[j] . attribute_length > 0)
	    		{
	    			methods[i] . attributes[j] . info = new u1[methods[i] . attributes[j] . attribute_length];
	    			for (unsigned int k = 0; k < methods[i] . attributes[j] . attribute_length; k++)
	    			{
	    				methods[i] . attributes[j] . info[k] = getu1(p); p += 1;
	    			}
	    		}
	    		//if Attribute is "Code, save it to code_attr"
		    	std::string attr_value;
		    	getAttrName(methods[i] . attributes[j] . attribute_name_index, attr_value);
		    	if(attr_value.compare("Code") == 0){
		    		char * pA = (char *)methods[i] . attributes[j] . info;

		    		methods[i] . code_attr = new Code_attribute;

	    		    methods[i] . code_attr -> attribute_name_index 		= methods[i] . attributes[j] . attribute_name_index;
				    methods[i] . code_attr -> attribute_length			= methods[i] . attributes[j] . attribute_length;
				    methods[i] . code_attr -> max_stack					= getu2(pA); pA += 2;
				    methods[i] . code_attr -> max_locals				= getu2(pA); pA += 2;
				    methods[i] . code_attr -> code_length				= getu4(pA); pA += 4;
				    if(methods[i] . code_attr -> code_length > 0)
				    {
				    	methods[i] . code_attr -> code = new u1[methods[i] . code_attr -> code_length];
				    	memcpy(methods[i] . code_attr -> code, pA, methods[i] . code_attr -> code_length);
				    }
				    else
				    {
				    	methods[i] . code_attr -> code = NULL;
				    }
				    pA += methods[i] . code_attr -> code_length;
				    methods[i] . code_attr -> exception_table_length	= getu2(pA); pA += 2;
				    if(methods[i] . code_attr -> exception_table_length > 0)
				    {
				    	methods[i] . code_attr -> exception_table = new Exception_table[methods[i] . code_attr -> exception_table_length];
				    	for (int l = 0; l < methods[i] . code_attr -> exception_table_length; l++)
				    	{
				    		methods[i] . code_attr -> exception_table[l] . start_pc 	= getu2(pA); pA += 2;
								methods[i] . code_attr -> exception_table[l] . end_pc 		= getu2(pA); pA += 2;
								methods[i] . code_attr -> exception_table[l] . handler_pc 	= getu2(pA); pA += 2;
								methods[i] . code_attr -> exception_table[l] . catch_type 	= getu2(pA); pA += 2;
				    	}
				    }
				    methods[i] . code_attr -> attributes_count = getu2(pA); pA += 2;
				    if(methods[i] . code_attr -> attributes_count > 0)
				    {
					    methods[i] . code_attr -> attributes = new attribute_info[methods[i] . code_attr -> attributes_count];
					    for (int m = 0; m < methods[i] . code_attr -> attributes_count; m++)
					    {
								methods[i] . code_attr -> attributes[m] . attribute_name_index 	= getu2(pA); pA += 2;
								methods[i] . code_attr -> attributes[m] . attribute_length 		= getu4(pA); pA += 4;
								if( methods[i] . code_attr -> attributes[m] . attribute_length > 0)
								{
									methods[i] . code_attr -> attributes[m] . info = new u1[methods[i] . code_attr -> attributes[m] . attribute_length];
									for (unsigned int o = 0; o < methods[i] . code_attr -> attributes[m] . attribute_length; o++)
									{
										methods[i] . code_attr -> attributes[m] . info[o] = getu1(pA); pA += 1;
									}
								}
					    }
				    }
		    	}
	    	}
	    }
  	}
	return 0;
}

int ClassFile::loadAttributes(char * &p)
{
	attributes = new attribute_info[attributes_count];

	for (int i = 0; i < attributes_count; i++)
	{
		attributes[i] . attribute_name_index = getu2(p); p += 2;
    attributes[i] . attribute_length		 = getu4(p); p += 4;
    attributes[i] . info = new u1[attributes[i] . attribute_length];
    if(attributes[i] . attribute_length > 0)
    {
    	for (unsigned int j = 0; j < attributes[i] . attribute_length; j++)
    	{
    		attributes[i] . info[j] = getu1(p); p += 1;
    	}
    }
	}
	return 0;
}