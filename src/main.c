#include "vendors/raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  const size_t screen_width = 800;
  const size_t screen_height = 600;
  InitWindow(screen_width, screen_height, "Simple c engine");

  while (!WindowShouldClose()) {
    printf("%i %i\n", GetRenderWidth(), GetRenderHeight());

    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }
  CloseWindow();
  return EXIT_SUCCESS;
}
