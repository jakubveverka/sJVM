#ifndef OBJECTREF_HPP_
#define OBJECTREF_HPP_

#include "ref.hpp"

class ClassFile;

class ObjectRef : public Ref{
	private:

	public:
		ClassFile * classFile;

	public:
		ObjectRef(int p_index, ClassFile * p_classFile);		
		int getIndex() const;
};

#endif /* OBJECTREF_HPP_ */