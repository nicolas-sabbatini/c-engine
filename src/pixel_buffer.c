#include "pixel_buffer.h"

#include <stdlib.h>

PixelBuffer* new_pixel_buffer(unsigned int width, unsigned int height) {
  PixelBuffer* pixel_buffer =
      malloc(sizeof(PixelBuffer) + sizeof(Pixel) * width * height);
  if (pixel_buffer) {
    pixel_buffer->width = width;
    pixel_buffer->height = height;
  }
  return pixel_buffer;
}

void clear_pixel_buffer(PixelBuffer* pixel_buffer, Pixel color) {
  for (unsigned int i = 0; i < pixel_buffer->height * pixel_buffer->width; i++) {
    pixel_buffer->buffer[i] = color;
  }
}

void shader_pixel_buffer(
    PixelBuffer* pixel_buffer,
    Pixel (*shader)(unsigned int, unsigned int, PixelBuffer*, void*),
    void* context) {
  for (unsigned int y = 0; y < pixel_buffer->height; y++) {
    for (unsigned int x = 0; x < pixel_buffer->width; x++) {
      pixel_buffer->buffer[(y * pixel_buffer->width) + x] =
          shader(x, y, pixel_buffer, context);
    }
  }
}

void rectangle_pixel_buffer(
    PixelBuffer* pixel_buffer,
    int ox,
    int oy,
    unsigned int width,
    unsigned int height,
    Pixel color) {
  for (unsigned int y = 0; y <= height; y++) {
    unsigned int target_y = y + oy;
    if (target_y >= pixel_buffer->height) {
      continue;
    }
    for (unsigned int x = 0; x <= width; x++) {
      unsigned int target_x = x + ox;
      if (target_x >= pixel_buffer->width) {
        continue;
      }
      poke_pixel_buffer(pixel_buffer, target_x, target_y, color);
    }
  }
}

void poke_pixel_buffer(PixelBuffer* pixel_buffer, int x, int y, Pixel color) {
  if (x > 0 && x < (int)pixel_buffer->width && y > 0 && y < (int)pixel_buffer->height) {
    pixel_buffer->buffer[(y * pixel_buffer->width) + x] = color;
  }
}

