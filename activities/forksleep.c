#include <stdio.h>
#include <unistd.h>

int main() {

  fork();

  for (int i = 0; i < 20; i++) {
    printf("eeping\n");
    sleep(2);
  }
  printf("done\n");
}
