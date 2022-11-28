// TRACE.

#include "user/user.h"

int
main(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(STDERR, "usage: trace mask program [args...]\n");
    exit(1);
  }
  char* end;
  int mask = strtoi(argv[1], &end, 10);
  if (argv[1] + strlen(argv[1]) != end) {
    fprintf(2, "trace: invalid mask '%s'\n", argv[1]);
    exit(1);
  }
  trace(mask);
  exec(argv[2], argv + 2);
  trace(0);
  exit(0);
}
