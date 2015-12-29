#ifndef STRINGOPERAND_HPP_
#define STRINGOPERAND_HPP_

#include <string>

#include "operand.hpp"

class StringOperand : public Operand {
	private:
		std::string value;
	public:
					StringOperand(std::string val);
		std::string	getStringValue() const;
		void 		setStringValue(std::string val);
			  		~StringOperand();
};

#endif /* STRINGOPERAND_HPP_ */
