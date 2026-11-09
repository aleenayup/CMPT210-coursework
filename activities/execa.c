#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t pid = fork();
  if (pid == 0) {
    execlp("ls", "ls", "-a", "-l", "-h", NULL);
  } else {
    execlp("ls", "ls", "-a", NULL);
  }
}
