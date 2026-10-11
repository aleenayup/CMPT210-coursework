
#define _DEFAULT_SOURCE

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXTRASIZE 256
#define BLOCKSIZE 128
#define BUFSIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void errorr(const char *message) {
  perror(message);
  exit(EXIT_FAILURE);
}

void printc(char *format, void *data, size_t ds) {
  char buf[BUFSIZE];

  int len =
      snprintf(buf, BUFSIZE, format, ds == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    errorr("snprintf");
  }

  write(STDOUT_FILENO, buf, (size_t)len);
}

int main(void) {
  // Request 256 bytes from the heap.
  void *start = sbrk(EXTRASIZE);

  if (start == (void *)-1) {
    errorr("sbrk");
  }

  struct header *first = (struct header *)start;
  struct header *second = (struct header *)((char *)start + BLOCKSIZE);

  first->size = BLOCKSIZE;
  first->next = NULL;

  second->size = BLOCKSIZE;
  second->next = first;

  printc("first block:       %p\n", &first, sizeof(first));
  printc("second block:      %p\n", &second, sizeof(second));

  printc("first block size:  %lu\n", &first->size, sizeof(first->size));
  printc("first block next:  %p\n", &first->next, sizeof(first->next));

  printc("second block size: %lu\n", &second->size, sizeof(second->size));
  printc("second block next: %p\n", &second->next, sizeof(second->next));

  size_t header_size = sizeof(struct header);
  size_t ds = BLOCKSIZE - header_size;

  char *fd = (char *)first + header_size;
  char *sd = (char *)second + header_size;

  memset(fd, 0, ds);
  memset(sd, 1, ds);

  printc("first block size:  %lu\n", &first->size, sizeof(first->size));
  printc("first block next:  %p\n", &first->next, sizeof(first->next));

  printc("second block size: %lu\n", &second->size, sizeof(second->size));
  printc("second block next: %p\n", &second->next, sizeof(second->next));

  for (size_t i = 0; i < ds; i++) {
    uint64_t val = (unsigned char)fd[i];
    printc("%lu\n", &val, sizeof(val));
  }

  for (size_t i = 0; i < ds; i++) {
    uint64_t val = (unsigned char)sd[i];
    printc("%lu\n", &val, sizeof(val));
  }

  return 0;
}
