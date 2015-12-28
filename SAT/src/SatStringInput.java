import java.io.*;
import java.util.Scanner;

public class SatStringInput {

    public static int getElementOnIPosition(int i, int combination) {
        int andOperator = 1;
        for(int j = 0; j < i; j++) andOperator = andOperator << 1;
        if((combination & andOperator) == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    public static int getIndexOfClosingBracket(String string, int startIndex) {
        int countOfOpeningBrackets = 1;
        for(int i = startIndex; i < string.length(); i++) {
            if(string.charAt(i) == ')') {
                countOfOpeningBrackets--;
                if(countOfOpeningBrackets == 0) return i;
            } else if(string.charAt(i) == '(') {
                countOfOpeningBrackets++;
            }
        }
        return -1;
    }

    public static int solve(String formula, int combination) {
        //System.out.println("formula --> " + formula);
        if(formula.length() == 1) return getElementOnIPosition(formula.charAt(0) - 'a', combination);

        int prevResult = -1;
        for(int i = 0, j = 0; i < formula.length()-1; i = j) {
            int moduloAdd = 0;
            int moduloAdd0 = 0;
            int partResult;
            int nextResult;
            if(formula.charAt(0) == '(') {
                i = getIndexOfClosingBracket(formula, 1);
                partResult = solve(formula.substring(1, i), combination);
            } else {
                if (prevResult == -1) {
                    if (formula.charAt(i) == '!') moduloAdd0 = 1;
                    i += moduloAdd0;
                    partResult = (getElementOnIPosition(formula.charAt(i) - 'a', combination) + moduloAdd0) % 2;
                } else {
                    partResult = prevResult;
                }
            }
            //System.out.println(formula + ": prevResult --> " + partResult);

            if(formula.charAt(i+4) == '!') moduloAdd = 1;

            if(formula.charAt(i+4+moduloAdd) == '(') {
                j = getIndexOfClosingBracket(formula, i+4+moduloAdd+1);
                nextResult = (solve(formula.substring(i+4+moduloAdd+1, j), combination) + moduloAdd) % 2;
            } else {
                nextResult = (getElementOnIPosition(formula.charAt(i + 4 + moduloAdd) - 'a', combination) + moduloAdd) % 2;
                j = i + 4 + moduloAdd;
            }
            //System.out.println(formula + ": nextResult --> " + nextResult);

            if(formula.charAt(i+2) == '|') {
                if(partResult == 1 || nextResult == 1) prevResult = 1;
                else prevResult = 0;
            } else if(formula.charAt(i+2) == '&') {
                if(partResult == 1 && nextResult == 1) prevResult = 1;
                else prevResult = 0;
            }
        }
        //System.out.println(formula + ": result = " + prevResult);
        return prevResult;
    }

    public static void main(String[] args) throws IOException {
        int elementsCount;
        int result;
        int isTrue = 0;

        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        Scanner inputFile;
        BufferedWriter outputFile;
        String inputFileName, outputFileName;

        System.out.println("Enter input file: ");
        //inputFileName = stdin.readLine(); //TODO
        inputFileName = "input.txt";
        System.out.println("Enter output file: ");
        //outputFileName = stdin.readLine(); //TODO
        outputFileName = "output.txt";
        stdin.close();

        //inputFile = new BufferedReader(new FileReader(inputFileName));
        inputFile = new Scanner(new File(inputFileName));
        outputFile = new BufferedWriter(new FileWriter(outputFileName));

        elementsCount = inputFile.nextInt();
        inputFile.nextLine(); //skipping line
        String formula = inputFile.nextLine();
        inputFile.close();

        formula = formula.substring(1, formula.length()-1); // skip beginning '(' and ending ')'

        int countOfPossibleCombinations = 1;
        for(int i = 0; i < elementsCount; i++) countOfPossibleCombinations *= 2;

        for(int combination = 0; combination < countOfPossibleCombinations; combination++) {
            System.out.println("Testing combination " + Integer.toBinaryString(combination));
            result = solve(formula, combination);
            if(result == 1) {
                System.out.println("----> SAT splnitelny pro " + Integer.toBinaryString(combination));
                outputFile.write("SAT splnitelny pro " + Integer.toBinaryString(combination) + "\n");
                isTrue = 1;
            }
        }
        if(isTrue == 0) {
            System.out.println("SAT nesplnitelny.");
            outputFile.write("SAT nesplnitelny.");
        }
        outputFile.flush();
        outputFile.close();
    }
}
