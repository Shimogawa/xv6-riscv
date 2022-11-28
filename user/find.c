// FIND.

#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

void
find(char buf[512], char* bufp, char* cur, char* pat) {
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(buf, 0)) < 0) {
    fprintf(2, "find: cannot open %s\n", buf);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", buf);
    close(fd);
    return;
  }

  switch (st.type) {
  case T_DEVICE:
  case T_FILE:
    // printf("compare '%s' and '%s' with path '%s'\n", cur, pat, buf);
    if (strcmp(cur, pat) == 0) {
      printf("%s\n", buf);
    }
    break;
  case T_DIR:
    if (strlen(buf) + 1 + DIRSIZ + 1 > 512) {
      printf("find: path too long\n");
      break;
    }
    *bufp++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;
      strcpy(bufp, de.name);
      find(buf, bufp + strlen(de.name), de.name, pat);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(STDERR, "usage: find <dir> <pattern>\n");
    exit(1);
  }
  char buf[512];
  char* p = buf;
  strcpy(buf, argv[1]);
  p = buf + strlen(buf);
  *p = 0;
  find(buf, p, argv[1], argv[2]);
  exit(0);
}
