#ifndef OPERAND_HPP_
#define OPERAND_HPP_

class Operand{
	private:

	public:
		virtual int getValue() const;
		virtual void setValue(int val);
		virtual ~Operand() {}
};

#endif /* OPERAND_HPP_ */
