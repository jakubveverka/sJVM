package test;

public class Func {
    public static boolean isGreaterThan5(int number)
    {
        boolean ret = false;
        if(number > 5)
        {
            ret = true;
        }
        else ret = false;
        return ret;
    }

    public static int multiply5(int number){
        int ret = 0;
        for (int i = 0; i < 5; i++) {
            ret+=number;
        }
        return ret;
    }

}
