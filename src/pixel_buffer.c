#include "pixel_buffer.h"
#include <stdlib.h>

PixelBuffer *new_pixel_buffer(unsigned int width, unsigned int height) {
  PixelBuffer *pixel_buffer =
      malloc(sizeof(PixelBuffer) + sizeof(Pixel) * width * height);
  if (pixel_buffer) {
    pixel_buffer->width = width;
    pixel_buffer->height = height;
  }
  return pixel_buffer;
}

void clear_pixel_buffer(PixelBuffer *pixel_buffer, Pixel color) {
  for (unsigned int y = 0; y < pixel_buffer->height; y++) {
    for (unsigned int x = 0; x < pixel_buffer->width; x++) {
      pixel_buffer->buffer[(y * pixel_buffer->width) + x] = color;
    }
  }
}

void shader_pixel_buffer(
    PixelBuffer *pixel_buffer,
    Pixel (*shader)(unsigned int, unsigned int, PixelBuffer *, void *),
    void *context) {
  for (unsigned int y = 0; y < pixel_buffer->height; y++) {
    for (unsigned int x = 0; x < pixel_buffer->width; x++) {
      pixel_buffer->buffer[(y * pixel_buffer->width) + x] =
          shader(x, y, pixel_buffer, context);
    }
  }
}
