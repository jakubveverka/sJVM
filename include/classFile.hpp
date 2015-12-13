#ifndef CLASSFILE_HPP_
#define CLASSFILE_HPP_

#include "definitions.hpp"

typedef struct {
    u2   attribute_name_index;
    u4   attribute_length;
    u1 * info; //[attribute_length]
} attribute_info;

typedef struct {
    u2               access_flags;
    u2               name_index;
    u2               descriptor_index;
    u2               attributes_count;
    attribute_info * attributes; //[attributes_count]
} method_info;

typedef struct {
    u2               access_flags;
    u2               name_index;
    u2               descriptor_index;
    u2               attributes_count;
    attribute_info * attributes; //[attributes_count]
} field_info;

typedef struct {
    u1 tag;
    u1 info[];
} cp_info;
 
class ClassFile {

	private:
		u4             		magic;
		u2             		minor_version;
		u2             		major_version;
		u2             		constant_pool_count;
		cp_info      	 ** constant_pool; //[constant_pool_count-1]
		u2             		access_flags;
		u2             		this_class;
		u2             		super_class;
		u2             		interfaces_count;
		u2           		* interfaces; //[interfaces_count]
		u2             		fields_count;
		field_info   	  * fields; //[fields_count]
		u2             		methods_count;
		method_info     *	methods; //[methods_count]
		u2             		attributes_count;
		attribute_info  * attributes; //[attributes_count]

	public:
		int loadClass(char * classFileName);
		
	private:
		int loadConstants(char * &p);
		int getConstantSize(char * &p);
		int loadInterfaces(char * &p);
		int loadFields(char * &p);
};

#endif /* CLASSFILE_HPP_ */
