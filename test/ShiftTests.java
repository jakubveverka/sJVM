package test;

class ShiftTests
{
	public static void main(String argc[])
	{
		int x, y, z;
		x = 2;
		y = 3;
		z = x << y;

		x = 16;
		z = x >> y;
		x = -196;
		z = x >> y;
		z = x >>> y;
	}
}
