
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTSIZE 5

void addToHist(char *hist[], int *count, char *line) {
  if (*count == HISTSIZE) {
    free(hist[0]);

    for (int i = 1; i < HISTSIZE; i++) {
      hist[i - 1] = hist[i];
    }

    (*count)--;
  }

  hist[*count] = line;
  (*count)++;
}

void printHist(char *hist[], int count) {
  for (int i = 0; i < count; i++) {
    printf("%s", hist[i]);
  }
}

void freeHist(char *hist[], int count) {
  for (int i = 0; i < count; i++) {
    free(hist[i]);
  }
}

int main(void) {
  char *hist[HISTSIZE] = {NULL};
  int count = 0;

  char *line = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter input: \n");
    fflush(stdout);

    if (getline(&line, &size, stdin) == -1) {
      break;
    }

    if (strcmp(line, "print\n") == 0 || strcmp(line, "print") == 0) {
      addToHist(hist, &count, line);
      printHist(hist, count);

      line = NULL;
      size = 0;
    } else {
      addToHist(hist, &count, line);
      line = NULL;
      size = 0;
    }
  }
  free(line);
  freeHist(hist, count);
  return 0;
}
