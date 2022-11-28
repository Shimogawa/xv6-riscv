#ifndef U_USER_H
#define U_USER_H

#include "kernel/types.h"

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define NULL 0

// stdbool
typedef char bool;

#define TRUE  1
#define FALSE 0

struct stat;
struct sysinfo;

// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int[2]);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int trace(int);
int sysinfo(struct sysinfo*);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void* memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char getc();
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int strtoi(const char*, char**, int);
int memcmp(const void*, const void*, uint);
void* memcpy(void*, const void*, uint);

#endif // U_USER_H
