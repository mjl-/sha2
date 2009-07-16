typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long uvlong;

typedef struct Uvvlong Uvvlong;
struct Uvvlong {
	uvlong	hi, lo;
};

#define nil	NULL
#define nelem(v)	(sizeof (v)/sizeof ((v)[0]))
