package test;

class ClassD {

	int a;
	ClassA ca;

	public ClassD(int b) {
		a = b;
		ca = new ClassA(a,a);
	}

	public void addOne() {
		a = a + 2;
	}

}
