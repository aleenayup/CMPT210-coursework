#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  for (int i = 0; i < 9; i++) {
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork failed wah wah");
      return 1;
    } else if (pid == 0) {
      printf("child %d\n", i);
      _exit(0);
    }
  }
  for (int sec = 0; sec < 10; sec++) {
    printf("still waiting\n");
    fflush(stdout);
    sleep(1);
  }
  return 0;
}
