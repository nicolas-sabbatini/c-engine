#pragma once

#include <math.h>

typedef struct Vec2 {
  float_t x;
  float_t y;
} Vec2;

Vec2 vec2_transform(Vec2 in, Vec2 transformation);
Vec2 vec2_transform_scalar(Vec2 in, float_t transformation);

Vec2 vec2_scale(Vec2 in, Vec2 transformation);
Vec2 vec2_scale_scalar(Vec2 in, float_t transformation);

Vec2 vec2_sub(Vec2 in, Vec2 transformation);
Vec2 vec2_sub_scalar(Vec2 in, float_t transformation);

Vec2 vec2_rotate(Vec2 in, float_t angle);

typedef struct Vec3 {
  float_t x;
  float_t y;
  float_t z;
} Vec3;

Vec3 vec3_transform(Vec3 in, Vec3 transformation);
Vec3 vec3_transform_scalar(Vec3 in, float_t transformation);

Vec3 vec3_scale(Vec3 in, Vec3 transformation);
Vec3 vec3_scale_scalar(Vec3 in, float_t transformation);

Vec3 vec3_sub(Vec3 in, Vec3 transformation);
Vec3 vec3_sub_scalar(Vec3 in, float_t transformation);

Vec3 vec3_rotate_z(Vec3 in, float_t angle);
Vec3 vec3_rotate_y(Vec3 in, float_t angle);
Vec3 vec3_rotate_x(Vec3 in, float_t angle);
