// PING PONG

#include "user/user.h"

void
do_child(int readfd, int writefd) {
  char buf;
  read(readfd, &buf, 1);
  printf("%d: received ping\n", getpid());
  write(writefd, &buf, 1);
}

void
do_parent(int readfd, int writefd) {
  char msg = 'a';
  char buf;
  write(writefd, &msg, 1);
  read(readfd, &buf, 1);
  printf("%d: received pong\n", getpid());
}

int
main(int argc, char* argv[]) {
  int to_child_fd[2];  // r, w
  int to_parent_fd[2]; // r, w
  if (pipe(to_child_fd) < 0) {
    fprintf(STDERR, "unable to make pipe\n");
    exit(1);
  }
  if (pipe(to_parent_fd) < 0) {
    fprintf(STDERR, "unable to make pipe\n");
    exit(1);
  }
  int cpid = fork();
  if (cpid < 0) {
    fprintf(STDERR, "unable to fork\n");
    exit(1);
  }
  if (cpid == 0) { // child
    close(to_child_fd[1]);
    close(to_parent_fd[0]);
    do_child(to_child_fd[0], to_parent_fd[1]);
    close(to_child_fd[0]);
    close(to_parent_fd[1]);
    exit(0);
  }
  // parent
  close(to_parent_fd[1]);
  close(to_child_fd[0]);
  do_parent(to_parent_fd[0], to_child_fd[1]);
  close(to_parent_fd[0]);
  close(to_child_fd[1]);
  exit(0);
}
