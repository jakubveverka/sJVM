#ifndef REF_HPP
#define REF_HPP

class Ref{
	private:

	public:		
		int heapIndex;
	public:
		Ref(int p_index);	
	virtual int getIndex() const = 0;	
};

#endif /* REF_HPP */