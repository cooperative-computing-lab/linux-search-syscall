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
  printf("%p %p %d %zu %p\n", "a", "b", 1, sizeof(buf), buf);
  fflush(stdout);
    fflush(stdout);
    errno = 0;
    //result = syscall(380, "/etc:/home:/usr", "*", 1, sizeof(buf), buf);
    result = syscall(380, "/usr/lib", "*", 1, sizeof(buf), buf);
    fflush(stdout);
    printf("syscall: result = %d: %s\n", result, strerror(errno));
    if (result > 0) {
      for (entry = buf; *entry; entry = entry+strlen(entry)+1)
        printf("matched: `%s'\n", entry);
    }
    fflush(stdout);
    return 1;
  return 0;
}
