package test;

class GarbageCollectorArrayTest
{
         public static void test() {
            int[] a = new int[3];

            test2();
         }

         public static void test2() {
            int[] c = new int[1];
         }

        public static void main(String argc[])
        {
          int[] a = new int[2];

          test();

          int[] b = new int[3];
        }
}
