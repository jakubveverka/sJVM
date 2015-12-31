#ifndef ARRAYREF_HHPP
#define ARRAYREF_HHPP

#include "ref.hpp"

class ArrayRef : public Ref{
	private:

	public:
		char arrayType;
	public:
		ArrayRef(int p_index, char p_arrayType);
		~ArrayRef() {};
};

#endif /* ARRAYREF_HHPP */
