package test;


class ClassB extends ClassA{
	int a;
	int b;

	public ClassB(int pA, int pB){
		super(pA + pB, pA - pB);
		a = pA;
		b = pB;
	}

	public int sumB(){
		return a + b;
	}
}