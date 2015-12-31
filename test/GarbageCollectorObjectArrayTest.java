package test;

class GarbageCollectorObjectArrayTest
{
         public static void test() {
            int[][] a = new int[2][2];

            test2();
         }

         public static void test2() {
            int[] c = new int[1];
         }

        public static void main(String argc[])
        {
          int[][] a = new int[2][1];

          test();

          int[] b = new int[2];
        }
}
