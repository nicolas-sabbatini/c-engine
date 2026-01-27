#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel_buffer.h"
#include "vendors/raylib.h"

Pixel cheker_board(
    unsigned int x, unsigned int y, __attribute__((unused)) PixelBuffer* pixel_buffer, __attribute__((unused)) void* context) {
  if (((x / 50) % 2 == 0 && (y / 50) % 2 == 0) ||
      ((x / 50) % 2 == 1 && (y / 50) % 2 == 1)) {
    return COLOR_RGB(0x101010);
  }
  return COLOR_RGB(0xE0E0E0);
}

int main() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_UNDECORATED | FLAG_VSYNC_HINT);
  size_t screen_width = 0;
  size_t screen_height = 0;
  InitWindow(screen_width, screen_height, "Simple c engine");
  SetTargetFPS(60);
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  screen_width = GetMonitorWidth(monitor) / 2;
  screen_height = GetMonitorHeight(monitor) / 2;

  PixelBuffer* pixel_buffer = new_pixel_buffer(screen_width, screen_height);
  clear_pixel_buffer(pixel_buffer, COLOR_RGB(0xFF0000));

  Image img = {
      .data = pixel_buffer->buffer,
      .width = pixel_buffer->width,
      .height = pixel_buffer->height,
      .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
      .mipmaps = 1,
  };
  Texture2D texture = LoadTextureFromImage(img);

  while (!WindowShouldClose()) {
    // Update texture
    shader_pixel_buffer(pixel_buffer, cheker_board, NULL);
    rectangle_pixel_buffer(pixel_buffer, 400, 400, 500, 500, COLOR_RGB(0xDD0000));
    // Send changes to GPU
    UpdateTexture(texture, pixel_buffer->buffer);

    // Draw to screen
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureEx(texture, (Vector2){}, 0, 2.0, WHITE);
    DrawFPS(10, 10);
    EndDrawing();
  }

  free(pixel_buffer);
  UnloadTexture(texture);

  CloseWindow();
  return EXIT_SUCCESS;
}
