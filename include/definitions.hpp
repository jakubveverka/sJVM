
typedef unsigned char  	u1;
typedef unsigned short	u2;
typedef unsigned int		u4;
typedef unsigned long		u8;

#define getu2(p) (u2)((p)[0] << 8  | (p)[1]);
#define getu4(p) (u4)((p)[0] << 24 | (p)[1] << 16 | (p)[2] << 8 | (p)[3]);
