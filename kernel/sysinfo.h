#ifndef K_SYSINFO_H
#define K_SYSINFO_H

#include "kernel/types.h"

struct sysinfo {
  uint64 freemem;
  uint nproc;
};

#endif // K_SYSINFO_H
