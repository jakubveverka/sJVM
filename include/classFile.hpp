#ifndef CLASSFILE_HPP_
#define CLASSFILE_HPP_

#include <string>

#include "definitions.hpp"


struct attribute_info;
class ClassHeap;

/*
 * Attributes types
*/

// help struct for Code_attribute
typedef struct Exception_table{
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
} Exception_table;

typedef struct Code_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 * code; //[code_length];
    u2 exception_table_length;
    Exception_table * exception_table; //[exception_table_length];
    u2 attributes_count;
    attribute_info * attributes; //[attributes_count];
} Code_attribute;

/*
 * types for classfile structure
 */

typedef struct attribute_info{
	  u2   attribute_name_index;
	  u4   attribute_length;
	  u1 * info; //[attribute_length]
} attribute_info;

typedef struct method_info{
    u2               access_flags;
    u2               name_index;
    u2               descriptor_index;
    u2               attributes_count;
    attribute_info * attributes; //[attributes_count]
} method_info;

typedef struct method_info_w_code : method_info{
		Code_attribute * code_attr;
} method_info_w_code;

typedef struct field_info{
    u2               access_flags;
    u2               name_index;
    u2               descriptor_index;
    u2               attributes_count;
    attribute_info * attributes; //[attributes_count]
} field_info;

typedef struct cp_info{
    u1 tag;
    u1 info[];
} cp_info;

//Class file data structure
class ClassFile {

	private:
	public:
		u4             				magic;
		u2             				minor_version;
		u2             				major_version;
		u2             				constant_pool_count;
		cp_info      	 	 	 ** constant_pool; //[constant_pool_count-1]
		u2             				access_flags;
		u2             				this_class;
		u2             				super_class;
		u2             				interfaces_count;
		u2           				* interfaces; //[interfaces_count]
		u2             				fields_count;
		field_info   	  		* fields; //[fields_count]
		u2             				methods_count;
		method_info_w_code 	* methods; //[methods_count]
		u2             				attributes_count;
		attribute_info  		* attributes; //[attributes_count]

		ClassHeap * classHeap;

		int loadClass(std::string classFileName);
		method_info_w_code getMethod(std::string methodName, std::string methodDescription);
		ClassFile * 			 setClassByMethod(std::string p_methodName, std::string p_methodDescription);

		int 				getAttrName(u2 attr_name_index, std::string &attr_name);
		int 				getObjectSize();
		int 				getFieldCount();
								ClassFile(ClassHeap * pClassHeap) : classHeap(pClassHeap) {};
		std::string getClassNameFromRef(u2 classNameIndex);
		std::string getName();
		int 				getFieldIndex(std::string fieldName);

	private:
		int loadConstants(char * &p);
		int getConstantSize(char * &p);
		int loadInterfaces(char * &p);
		int loadFields(char * &p);
		int loadMethods(char * &p);
		int loadAttributes(char * &p);
};

#endif /* CLASSFILE_HPP_ */
