
public class SatIntInput {

    public static int getElementOnIPosition(int i, int combination) {
        int andOperator = 1;
        for(int j = 0; j < i; j++) andOperator = andOperator << 1;
        if((combination & andOperator) == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    public static void main(String[] args) {
        // -1 == or
        // -2 == and
        // -3 == neg
        //int elementsCount = 4;
        //int[] formula = {0,-2,1,-1,2,-2,-3,3};
        //int elementsCount = 2;
        //int[] formula = {0,-2,-3,0,-2,1};
        int elementsCount = 2;
        int[][] formula = {{-3}, {0},{-1},{0},{-2},{1}};
        //int elementsCount = 2;
        //int[] formula = {-3, 0,-1,0,-2,1};
        int[] results = new int[formula.length];
        int isTrue = 0;

        int countOfPossibleCombinations = 1;
        for(int i = 0; i < elementsCount; i++) countOfPossibleCombinations *= 2;

        for(int combination = 0; combination < countOfPossibleCombinations; combination++) {
            System.out.println("Testing combination " + Integer.toBinaryString(combination));
            for(int i = 0; i < formula.length-1; i+=2) {
                int moduloAdd = 0;
                int partResult;
                int nextResult;
                if(i == 0) {
                    if(formula[i][0] == -3) {
                        partResult = (getElementOnIPosition(formula[i+1][0], combination)+1) % 2;
                        i += 1;
                    } else {
                        partResult = getElementOnIPosition(formula[i][0], combination);
                    }
                } else {
                    partResult = results[i];
                }
                if(formula[i+2][0] == -3) {
                    moduloAdd = 1;
                }
                nextResult = (getElementOnIPosition(formula[i+2+moduloAdd][0], combination) + moduloAdd)%2;
                if(formula[i+1][0] == -1) {
                    if(partResult == 1 || nextResult == 1) results[i+moduloAdd+2] = 1;
                    else results[i+moduloAdd+2] = 0;
                } else if(formula[i+1][0] == -2) {
                    if(partResult == 1 && nextResult == 1) results[i+moduloAdd+2] = 1;
                    else results[i+moduloAdd+2] = 0;
                }
                i += moduloAdd;
            }
            if(results[results.length-1] == 1) {
                System.out.println("----> SAT splnitelny pro " + Integer.toBinaryString(combination));
                isTrue = 1;
            }
        }
        if(isTrue != 1) System.out.println("SAT nesplnitelny.");
    }
}
