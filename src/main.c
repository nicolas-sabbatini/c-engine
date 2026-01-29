#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mesh.h"
#include "pixel_buffer.h"
#include "vectors.h"
#include "vendors/raylib.h"

const float_t fov_factor =  640.0;
const Vec3 camera_position = (Vec3){0.0, 0.0, -5.0};
float_t cube_rotation = 0.0;

Pixel cheker_board(
    unsigned int x, unsigned int y, __attribute__((unused)) PixelBuffer* pixel_buffer, __attribute__((unused)) void* context) {
  if (((x / 50) % 2 == 0 && (y / 50) % 2 == 0) ||
      ((x / 50) % 2 == 1 && (y / 50) % 2 == 1)) {
    return COLOR_RGB(0x101010);
  }
  return COLOR_RGB(0xE0E0E0);
}

void orthographic_projection(PixelBuffer* pixel_buffer, Vec3 vec, Pixel color) {
  Vec2 projected_point = (Vec2){vec.x * fov_factor, vec.y * fov_factor};
  int target_x = (int)(((float_t)pixel_buffer->width / 2) + projected_point.x);
  int target_y = (int)(((float_t)pixel_buffer->height / 2) + projected_point.y);

  rectangle_pixel_buffer(pixel_buffer, target_x, target_y, 5, 5, color);
}

void isometric_projection(PixelBuffer* pixel_buffer, Vec3 vec, Pixel color) {
  // Isometric projection formula:
  //   screen_x = (x - z) * cos(30°)
  //   screen_y = y + (x + z) * sin(30°)
  // Where cos(30°) ≈ 0.866 and sin(30°) = 0.5
  Vec2 projected_point = (Vec2){
      (vec.x - vec.z) * 0.866f * fov_factor,
      (-vec.y + (vec.x + vec.z) * 0.5f) * fov_factor};

  int target_x = (int)(((float_t)pixel_buffer->width / 2) + projected_point.x);
  int target_y = (int)(((float_t)pixel_buffer->height / 2) + projected_point.y);

  rectangle_pixel_buffer(pixel_buffer, target_x, target_y, 5, 5, color);
}

void perspective_projection(PixelBuffer* pixel_buffer, Vec3 vec, Pixel color) {
  Vec3 vec_rotated = vec3_rotate_x(vec, cube_rotation);
  vec_rotated = vec3_rotate_y(vec_rotated, cube_rotation);
  vec_rotated = vec3_rotate_z(vec_rotated, cube_rotation);

  Vec2 projected_point = (Vec2){
      (vec_rotated.x * fov_factor) / (vec_rotated.z - camera_position.z),
      (-vec_rotated.y * fov_factor) / (vec_rotated.z - camera_position.z)};

  int target_x = (int)(((float_t)pixel_buffer->width / 2) + projected_point.x);
  int target_y = (int)(((float_t)pixel_buffer->height / 2) + projected_point.y);

  float_t distance = vec_rotated.z - camera_position.z;
  float_t max_distance = 10.0f;
  float_t brightness = 1.0f - (distance / max_distance);

  if (brightness < 0.0f) brightness = 0.0f;
  if (brightness > 1.0f) brightness = 1.0f;

  Pixel shaded_color = (Pixel){
      .r = (uint8_t)(color.r * brightness),
      .g = (uint8_t)(color.g * brightness),
      .b = (uint8_t)(color.b * brightness),
      .a = color.a,
  };

  rectangle_pixel_buffer(pixel_buffer, target_x, target_y, 10 * brightness, 10 * brightness, shaded_color);
}

int main() {
  // Set up screen
  SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_VSYNC_HINT);
  size_t screen_width = 0;
  size_t screen_height = 0;
  InitWindow(screen_width, screen_height, "Simple c engine");
  SetTargetFPS(60);
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  // 4k monitor is to much so 1024 x 640
  screen_width = GetMonitorWidth(monitor);
  screen_height = GetMonitorHeight(monitor);

  printf("Buffer size: %zu x %zu\n", screen_width, screen_height);

  // Create pixel buffer
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

  // Create a cube of points
  Vec3 cube[8] = {
    (Vec3){.x = -1.0, .y = -1.0, .z = -1.0},
    (Vec3){.x = -1.0, .y = 1.0, .z = -1.0},
    (Vec3){.x = 1.0, .y = 1.0, .z = -1.0},
    (Vec3){.x = 1.0, .y = -1.0, .z = -1.0},
    (Vec3){.x = 1.0, .y = 1.0, .z = 1.0},
    (Vec3){.x = 1.0, .y = -1.0, .z = 1.0},
    (Vec3){.x = -1.0, .y = 1.0, .z = 1.0},
    (Vec3){.x = -1.0, .y = -1.0, .z = 1.0}
  };
  size_t face_count = 12;
  Triangle mesh[12] = {
    // Front
    (Triangle){.a = 1, .b = 2, .c = 3},
    (Triangle){.a = 1, .b = 3, .c = 4},
    // right
    (Triangle){.a = 4, .b = 3, .c = 5},
    (Triangle){.a = 4, .b = 5, .c = 6},
    // back
    (Triangle){.a = 6, .b = 5, .c = 7},
    (Triangle){.a = 6, .b = 7, .c = 8},
    // left
    (Triangle){.a = 8, .b = 7, .c = 2},
    (Triangle){.a = 8, .b = 2, .c = 1},
    // top
    (Triangle){.a = 2, .b = 7, .c = 5},
    (Triangle){.a = 2, .b = 5, .c = 3},
    // bottom
    (Triangle){.a = 6, .b = 8, .c = 1},
    (Triangle){.a = 6, .b = 1, .c = 4},
  };

  while (!WindowShouldClose()) {
    float_t dt = GetFrameTime();
    cube_rotation += 1.0 * dt;
    // Update texture
    clear_pixel_buffer(pixel_buffer, COLOR_RGB(0x0F0F0F));
    for (size_t face = 0; face < face_count; face++) {
      perspective_projection(pixel_buffer, cube[mesh[face].a - 1], COLOR_RGB(0xF0A00F));
      perspective_projection(pixel_buffer, cube[mesh[face].b - 1], COLOR_RGB(0xF0A00F));
      perspective_projection(pixel_buffer, cube[mesh[face].c - 1], COLOR_RGB(0xF0A00F));
    }
    // Send changes to GPU
    UpdateTexture(texture, pixel_buffer->buffer);

    // Draw to screen
    BeginDrawing();
    ClearBackground(BLACK);
    // Scale to 4k
    DrawTextureEx(texture, (Vector2){}, 0, 1.0, WHITE);
    DrawFPS(10, 10);
    EndDrawing();
  }

  // Free pixel buffer
  free(pixel_buffer);
  UnloadTexture(texture);

  CloseWindow();
  return EXIT_SUCCESS;
}
