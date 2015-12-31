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

    public static int multiply5(int number, int number2, int number3){
        int ret = 0;
        for (int i = 0; i < 5; i++) {
            ret+=number;
        }
        return ret;
    }

    public static void test() {
       ClassD c5 = new ClassD(4);

       test2();

       c5.addOne();
   }

   public static void test2() {
      ClassD c3 = new ClassD(3);
      c3.addOne();
   }
}
