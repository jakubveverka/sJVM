
package test.our.objects;

public class FileWriter
{
   public static native int writeString(String fileName, String stringToWrite);
   public static native int writeInt(String fileName, int intToWrite);
}
