#pragma once

#include <stdint.h>

#define COLOR_HEX(hex)                \
  ((Pixel){.r = ((hex) >> 24) & 0xFF, \
           .g = ((hex) >> 16) & 0xFF, \
           .b = ((hex) >> 8) & 0xFF,  \
           .a = (hex) & 0xFF})

#define COLOR_RGB(hex)                \
  ((Pixel){.r = ((hex) >> 16) & 0xFF, \
           .g = ((hex) >> 8) & 0xFF,  \
           .b = (hex) & 0xFF,         \
           .a = 0xFF})

typedef struct Pixel {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Pixel;

typedef struct PixelBuffer {
  unsigned int width;
  unsigned int height;
  Pixel buffer[];
} PixelBuffer;

PixelBuffer* new_pixel_buffer(unsigned int width, unsigned int height);

void clear_pixel_buffer(PixelBuffer* pixel_buffer, Pixel color);

void shader_pixel_buffer(
    PixelBuffer* pixel_buffer,
    Pixel (*shader)(unsigned int x, unsigned int y, PixelBuffer* pixel_buffer, void* context),
    void* context);

void rectangle_pixel_buffer(
    PixelBuffer* pixel_buffer,
    unsigned int x,
    unsigned int y,
    unsigned int width,
    unsigned int height,
    Pixel color);