#include "debugMsg.hpp"

typedef unsigned char  	u1;
typedef unsigned short	u2;
typedef unsigned int		u4;
typedef unsigned long		u8;

#define ACC_PUBLIC 			0x0001
#define ACC_PRIVATE 		0x0002
#define ACC_PROTECTED 		0x0004
#define ACC_STATIC 			0x0008
#define ACC_FINAL 			0x0010
#define ACC_SYNCHRONIZED 	0x0020
#define ACC_BRIDGE 			0x0040
#define ACC_VARARGS 		0x0080
#define ACC_NATIVE 			0x0100
#define ACC_ABSTRACT 		0x0400
#define ACC_STRICT 			0x0800
#define ACC_SYNTHETIC 		0x1000

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

	#define getShort(p) (short)( \
		((short)((p)[0]) << 8  & 0x0000FF00) | \
		     ((p)[1]) \
		);

#define getu4(p) (u4)( \
	((u4)((p)[0]) << 24 & 0xFF000000) | \
	((u4)((p)[1]) << 16 & 0x00FF0000) | \
	((u4)((p)[2]) << 8  & 0x0000FF00) | \
	((u4)((p)[3])	    & 0x000000FF)   \
	);

#define getTwoStackOperands(operation, frame, firstOperand, secondOperand) { \
	firstOperand = frame->topPopOperand(); \
	DEBUG_MSG(std::string(operation) + ": first operand: " + std::to_string(firstOperand->getValue())); \
	secondOperand = frame->topPopOperand(); \
	DEBUG_MSG(std::string(operation) + ": second operand: " + std::to_string(secondOperand->getValue())); \
};

#define getTwoBytesFromFrame(operation, frame, p, firstByte, secondByte) { \
	firstByte = (u1)p[frame -> getPc() + 1]; \
	DEBUG_MSG(std::string(operation) + ": first byte: " + std::to_string(firstByte)); \
	secondByte = (u1)p[frame -> getPc() + 2]; \
	DEBUG_MSG(std::string(operation) + ": second byte: " + std::to_string(secondByte)); \
};

#define getFourBytesFromFrame(operation, frame, p, firstByte, secondByte, thirdByte, fourthByte) { \
	getTwoBytesFromFrame(operation, frame, p, firstByte, secondByte); \
	thirdByte = (u1)p[frame -> getPc() + 3]; \
	DEBUG_MSG(std::string(operation) + ": third byte: " + std::to_string(thirdByte)); \
	fourthByte = (u1)p[frame -> getPc() + 4]; \
	DEBUG_MSG(std::string(operation) + ": fourt byte: " + std::to_string(fourthByte)); \
};
