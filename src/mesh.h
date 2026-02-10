#pragma once

#include <stddef.h>

#include "vectors.h"

typedef struct Triangle {
  size_t a;
  size_t b;
  size_t c;
} Triangle;

// Test data
// Create a cube of points
Vec3 cube[8] = {
    (Vec3){.x = -1.0, .y = -1.0, .z = -1.0},
    (Vec3){.x = -1.0, .y = 1.0, .z = -1.0},
    (Vec3){.x = 1.0, .y = 1.0, .z = -1.0},
    (Vec3){.x = 1.0, .y = -1.0, .z = -1.0},
    (Vec3){.x = 1.0, .y = 1.0, .z = 1.0},
    (Vec3){.x = 1.0, .y = -1.0, .z = 1.0},
    (Vec3){.x = -1.0, .y = 1.0, .z = 1.0},
    (Vec3){.x = -1.0, .y = -1.0, .z = 1.0}};
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
