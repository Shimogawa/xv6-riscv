#ifndef C_STD_H
#define C_STD_H

typedef char bool;

#define TRUE  (char)1
#define FALSE (char)0

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

typedef uint64 size_t;

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#ifndef NULL
#define NULL 0
#endif

#endif // C_STD_H
