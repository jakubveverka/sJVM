#ifndef INTOPERAND_HPP_
#define INTOPERAND_HPP_

#include "operand.hpp"

class IntOperand : public Operand {
	private:
		int value;
	public:
				IntOperand(int val);
		int 	getValue() const;
		void 	setValue(int val);
			  	~IntOperand();
};

#endif /* INTOPERAND_HPP_ */
