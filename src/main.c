#define SOKOL_APP_IMPL
#define SOKOL_GLCORE
#define SOKOL_EGL
#include "vendors/sokol/sokol_app.h"
#include "vendors/sokol/sokol_gfx.h"

#include "globals.h"
#include <stdint.h>
#include <stdio.h>

void init() {
  printf("Game width: %d!\n", GAME_WIDTH);
  printf("Game height: %d!\n", GAME_HEIGHT);
}

void clean() { printf("Exit game\n"); }

void draw() {}

void update() {}

sapp_desc sokol_main(int argc, char *argv[]) {
  return (sapp_desc){
      .width = 640,
      .height = 480,
      .init_cb = init,
      .frame_cb = draw,
      .cleanup_cb = clean,
      .event_cb = update,
  };
}
