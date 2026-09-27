#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;
  ssize_t charsread;

  while (1) {
    printf("Enter programs to run: \n");

    charsread = getline(&buff, &size, stdin);

    if (charsread == -1) {
      printf("error wah wah\n");
      free(buff);
      return 1;
    }

    // to remove the newline from getline
    buff[charsread - 1] = '\0';

    pid_t pid = fork();

    if (pid == -1) {
      printf("fork failed wah wah\n");
      free(buff);
      return 1;
    }

    if (pid == 0) {
      // means this is the child
      execlp(buff, buff, NULL);

      printf("exec failed\n");
      free(buff);
      return 1;
    }

    else if (pid > 0) {
      // means this is da parent
      printf("im da parent fr\n");
      pid_t done = waitpid(pid, NULL, 0);

      if (done == -1) {
        printf("waitpid failed wah wah\n");
        free(buff);
        return 1;
      }
    }
    free(buff);
    return 0;
  }
}
