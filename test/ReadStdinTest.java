package test;

import test.our.objects.StdInputReader;
import test.our.objects.FileParserReader;
import test.our.objects.FileWriter;

public class ReadStdinTest {

	public static void main(String argc[])
	{
      StdInputReader r = new StdInputReader();
		FileParserReader fr = new FileParserReader();
		FileWriter fw = new FileWriter();

      String inputFile = r.readString();
		String outputFile = r.readString();

		int elementsCount = fr.readElementsCount(inputFile);

		if(elementsCount <= 0) {
			System.out.print("input file error");
			return;
		}

		int[][] formula = fr.readAndParseFormula(inputFile);

	}
}
