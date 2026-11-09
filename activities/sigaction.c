#define _POSIX_C_SOURCE 200809
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *msg = "herrow\m";

void handler(int signum) { write(STDOUT_FILENO, msg, strlen(msg)); }

int main(void) {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    sleep(1);
    kill(getppid(), SIGINT);
  } else {
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    int lol = sigaction(SIGINT, &act, NULL);

    if (lol == -1) {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }

    while (true) {
      sleep(1);
    }
  }
  return 0;
}
