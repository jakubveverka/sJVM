package test;

import static test.Func.test;

class GarbageCollectorTest
{
        public static void main(String argc[])
        {
          ClassA c1 = new ClassA(1,2);

          test();

          c1.sumA();

          ClassA c2 = new ClassA(1,2);

          c2.sumA();
        }
}
