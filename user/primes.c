// PRIMES

#include "user/user.h"

#define FORK()                                                                 \
  fork();                                                                      \
  if (cpid < 0) {                                                              \
    fprintf(STDERR, "failed to fork\n");                                       \
    exit(1);                                                                   \
  }

void
compute(int left_pipefd) {
  int p, n;
START:
  if (read(left_pipefd, &p, sizeof(int)) <= 0) {
    close(left_pipefd);
    return;
  }
  printf("(PID %d) prime %d\n", getpid(), p);
  int pipefd[2];
  if (pipe(pipefd) < 0) {
    fprintf(STDERR, "failed to create pipe\n");
    close(left_pipefd);
    exit(1);
  }
  int cpid;
  cpid = FORK();
  if (cpid == 0) { // spawn a right node
    left_pipefd = pipefd[0];
    close(pipefd[1]);
    goto START;
  }
  close(pipefd[0]);
  while (read(left_pipefd, &n, sizeof(int)) > 0) {
    if (n % p != 0) { // send to right pipe
      write(pipefd[1], &n, sizeof(int));
    }
  }
  close(left_pipefd);
  close(pipefd[1]);
}

int
main(int argc, char* argv[]) {
  int pipefd[2];
  if (pipe(pipefd) < 0) {
    fprintf(STDERR, "failed to create pipe\n");
    exit(1);
  }
  int cpid = FORK();
  if (cpid == 0) { // child
    close(pipefd[1]);
    compute(pipefd[0]);
    wait(NULL);
    exit(0);
  }
  close(pipefd[0]);
  for (int i = 2; i <= 35; i++) {
    write(pipefd[1], &i, sizeof(int));
  }
  close(pipefd[1]);
  wait(NULL);
  exit(0);
}
