package test;

import test.our.objects.FileParserReader;

public class DoubleArrayTest {

	public static void main(String argc[])
	{

      FileParserReader fr = new FileParserReader();

		int[][] array = fr.readAndParseFormula("input.txt");

      System.out.print("ahoj");
	}
}
