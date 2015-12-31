#ifndef OBJECTARRAYREF_HPP_
#define OBJECTARRAYREF_HPP_

#include "ref.hpp"
#include <string>

class ObjectArrayRef : public Ref{
	private:

	public:
		std::string className;
	public:
		ObjectArrayRef(int p_index, std::string p_className);
};

#endif /* OBJECTARRAYREF_HPP_ */
