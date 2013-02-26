#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/reboot.h>

#include "./linux/arch/x86/include/generated/asm/unistd_32.h"

char buf[1<<25];

int main(int argc, char ** argv) {
  int result;
  printf("%p %p %d %zu %p\n", "a", "b", 1, sizeof(buf), buf);
  fflush(stdout);
  pid_t child = fork();
  if (child == 0) {
    char *entry;
    result = setuid(1);
    printf("setuid: result = %d: %s\n", result, strerror(errno));
//    errno = 0;
//    result = syscall(380, "/lost+found:a:/etc:/usr/local/:/usr/./src//", "b", 1, sizeof(buf), buf);
//    printf("syscall: result = %d: %s\n", result, strerror(errno));
//    if (result > 0) {
//      for (entry = buf; *entry; entry = entry+strlen(entry)+1)
//        printf("matched: %s", entry);
//    }
    errno = 0;
    //result = syscall(380, "a:/etc/systemd:/usr/local/:/usr/./src//", "/usr/src/*|/?|linux-3.5.3-1-ARCH/*", 1, sizeof(buf), buf);
    fflush(stdout);
    result = syscall(380, "/etc:/usr", "*", 1, sizeof(buf), buf);
    fflush(stdout);
    printf("syscall: result = %d: %s\n", result, strerror(errno));
    if (result > 0) {
      for (entry = buf; *entry; entry = entry+strlen(entry)+1)
        printf("matched: `%s'\n", entry);
    }
    return 1;
  }
  wait(NULL);
  printf("powering down\n");
  fflush(stdout);
  result = reboot(RB_POWER_OFF);
  //int result = syscall(__NR_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2C, LINUX_REBOOT_CMD_POWER_OFF);
  printf("failed to powerdown: %d (%s)\n", result, strerror(result));
  return 0;
}
