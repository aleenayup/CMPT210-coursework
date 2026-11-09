#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t pid = fork();
  if (pid == 0) {
    printf("im child %d\n", getpid());
  } else {
    printf("im parent %d\n", getppid());
  }
}
