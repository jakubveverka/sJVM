#ifndef OPERAND_HPP_
#define OPERAND_HPP_

class Operand{
	private:

	public:
		virtual int getValue() const = 0;
		virtual void setValue(int val) = 0;
		virtual ~Operand() {}
};

#endif /* OPERAND_HPP_ */
