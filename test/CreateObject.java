package test;

import test.ClassA;
import test.ClassB;

class CreateObject{

	public static void main(String argc[]){

		ClassB obj2 = new ClassB(3, 4);

		/*
		int x = obj2 . x;
		int y = obj2 . y;
		int a = obj2 . a;
		int b = obj2 . b;
		int sumB = obj2 . sumB();
		*/
		int sumA = obj2 . sumA();	
	}
}