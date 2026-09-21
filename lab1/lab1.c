
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h?

int main(void) {

  char *buff = NULL;
  size_t size = 0;

  while (1) {
    printf("enter text");
    ssize_t num_char = getline(&buff, &size, stdin);
    if (num_char == -1) {
      perror("operation failed");
      error(EXIT_FAILURE);
    }
    char *saveptr;
    char *token = strtok_r(buff, " ", &saveptr);

    while (token != NULL) {
      printf(" %s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }

    free(buff);
    return (0);
  }
}
