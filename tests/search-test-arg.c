#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/reboot.h>

#include "./linux/arch/x86/include/generated/asm/unistd_32.h"

char buf[1<<27];

int main(int argc, char ** argv) {
  int result;
  char *entry;
  char *paths = ".";
  char *pattern = "*";
  if (argc > 1)
    paths = argv[1];
  if (argc > 2)
    pattern = argv[2];
  int flags = 4+2;
  printf("user: search(`%s', `%s', %d, %p, %d)\n", paths, pattern, flags, buf, sizeof(buf));
  errno = 0;
  fflush(stdout);
  result = syscall(319, paths, pattern, flags, buf, sizeof(buf));
  fflush(stdout);
  printf("syscall: result = %d: %s\n", result, strerror(errno));
  fflush(stdout);
  if (result > 0) {
    write(STDOUT_FILENO, buf, 1024);
    //for (entry = buf; *entry; entry = strchr(entry, '|'))
    //  printf("matched: `%s'\n", entry);
  }
  fflush(stdout);
  return 0;
}
