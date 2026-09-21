#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int p = getpid();
  int pp = getppid();

  printf("my PID is %d, and my parent PID is %d \n", p, pp);
  pid_t pid = fork();

  printf("when i run fork it gives this val: %d\n", pid);

  if (pid == 0) {
    printf("child PID is %d, parent PID is %d\n", getpid(), getppid());
  } else {
    printf("parent PID is %d, child PID is %d\n", getpid(), pid);
  }
}
