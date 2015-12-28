#ifndef REFOPERAND_HPP_
#define REFOPERAND_HPP_

#include "operand.hpp"

class RefOperand : public Operand {
	private:
		int index;
	public:
				RefOperand(int i);
		int 	getValue() const;
		void 	setValue(int i);
			  	~RefOperand();
};

#endif /* REFOPERAND_HPP_ */