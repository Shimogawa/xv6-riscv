// SLEEP

#include "user/user.h"

int
main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(2, "Usage: sleep <time>\n");
    exit(1);
  }

  char* end;
  int time = strtoi(argv[1], &end, 10);
  if (argv[1] + strlen(argv[1]) != end) {
    fprintf(2, "sleep: invalid time interval '%s'\n", argv[1]);
    exit(1);
  }
  sleep(time);
  exit(0);
}
