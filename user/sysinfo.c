// SYSINFO.

#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char* argv[]) {
  if (argc != 1) {
    fprintf(STDERR, "usage: sysinfo\n");
    exit(1);
  }
  struct sysinfo info;
  if (sysinfo(&info) < 0) {
    fprintf(STDERR, "sysinfo: unable to get system info\n");
    exit(1);
  }
  uint64 freemem = info.freemem;
  if (freemem / 1024 < 10) {
    printf("sysinfo\nfreemem: %l B\nnproc: %l\n", info.freemem, info.nproc);
    exit(0);
  }
  freemem /= 1024;
  if (freemem / 1024 < 10) {
    printf("sysinfo\nfreemem: %l KiB\nnproc: %l\n", (uint)freemem, info.nproc);
    exit(0);
  }
  freemem /= 1024;
  printf("sysinfo\nfreemem: %l MiB\nnproc: %l\n", (uint)freemem, info.nproc);
  exit(0);
}
