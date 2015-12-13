
typedef unsigned char  	u1;
typedef unsigned short	u2;
typedef unsigned int		u4;
typedef unsigned long		u8;

#define CONSTANT_Class  			7
#define CONSTANT_Fieldref  			9
#define CONSTANT_Methodref  		10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String  			8
#define CONSTANT_Integer  			3
#define CONSTANT_Float  			4
#define CONSTANT_Long  				5
#define CONSTANT_Double  			6
#define CONSTANT_NameAndType  		12
#define CONSTANT_Utf8  				1
#define CONSTANT_MethodHandle		15
#define CONSTANT_MethodType			16
#define CONSTANT_InvokeDynamic		18

#define getu1(p) (p)[0]
#define getu2(p) (u2)( \
	((u2)((p)[0]) << 8  & 0x0000FF00) | \
	     ((p)[1]) \
	);
#define getu4(p) (u4)( \
	((u4)((p)[0]) << 24 & 0xFF000000) | \
	((u4)((p)[1]) << 16 & 0x00FF0000) | \
	((u4)((p)[2]) << 8  & 0x0000FF00) | \
	((u4)((p)[3])	    & 0x000000FF)   \
	);
