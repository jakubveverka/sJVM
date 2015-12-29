#ifndef OPERAND_HPP_
#define OPERAND_HPP_

#include <string>

class Operand{
	private:

	public:
		virtual int getValue() const;
		virtual void setValue(int val);
		virtual std::string getStringValue() const;
		virtual void setStringValue(std::string val);
		virtual ~Operand() {}
};

#endif /* OPERAND_HPP_ */
