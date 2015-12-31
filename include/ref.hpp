#ifndef REF_HPP
#define REF_HPP

class Ref{
	private:
		int gcNumber = 0;
	public:
		int heapIndex;
	public:
		Ref(int p_index);
	virtual ~Ref() {};
	int getIndex() const;
	void setGcNumber(int pGcNumber);
	int  getGcNumber();
};

#endif /* REF_HPP */
