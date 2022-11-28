// SYSINFO.

#include "sysinfo.h"
#include "defs.h"
#include "proc.h"
#include "types.h"

int
sysinfo(uint64 addr) {
  struct sysinfo info;
  info.freemem = freememsz();
  info.nproc = proccnt();
  if (copyout(myproc()->pagetable, addr, (char*)&info, sizeof(info)) < 0) {
    return -1;
  }
  return 0;
}
