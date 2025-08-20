#include "globals.h"
#include <stdint.h>
#include <stdio.h>

void init() {
  printf("Game width: %d!\n", GAME_WIDTH);
  printf("Game height: %d!\n", GAME_HEIGHT);
}

void clean() { printf("Exit game\n"); }

int main(/*int argc, char *argv[]*/) {
  init();
  clean();
  return 0;
}
