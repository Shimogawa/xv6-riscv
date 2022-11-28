// XARGS.

#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char* argv[]) {
  if (argc <= 1) {
    fprintf(STDERR, "usage: xargs <cmd> [args...]\n");
    exit(1);
  }
  char buf[ARGSTR_MAX];
  char* cmd = argv[1];
  char* args[MAXARG];
  int i;
  for (i = 0; i < argc - 1; i++) {
    args[i] = argv[i + 1];
  }
  char* bufp = buf;
  char c;
  while ((c = getc())) {
    if (c == '\n') {
      if (bufp == buf) {
        continue;
      }
      *bufp = 0;
      args[i] = buf;
      args[i + 1] = 0;
      int cpid = fork();
      if (cpid < 0) {
        fprintf(STDERR, "error: cannot fork\n");
        exit(1);
      }
      if (cpid == 0) {
        exit(exec(cmd, args));
      }
      bufp = buf;
    } else {
      if (bufp >= buf + ARGSTR_MAX - 1) {
        continue;
      }
      *bufp++ = c;
    }
  }
  wait(NULL);
  exit(0);
}
