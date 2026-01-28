#include "vectors.h"

Vec2 vec2_transform(Vec2 in, Vec2 transformation) {
  return (Vec2){
      .x = in.x + transformation.x,
      .y = in.y + transformation.y,
  };
}

Vec2 vec2_transform_scalar(Vec2 in, float_t transformation) {
  return (Vec2){
      .x = in.x + transformation,
      .y = in.y + transformation,
  };
}

Vec2 vec2_scale(Vec2 in, Vec2 scale) {
  return (Vec2){
      .x = in.x * scale.x,
      .y = in.y * scale.y,
  };
}

Vec2 vec2_scale_scalar(Vec2 in, float_t scale) {
  return (Vec2){
      .x = in.x * scale,
      .y = in.y * scale,
  };
}

Vec2 vec2_sub(Vec2 in, Vec2 transformation) {
  return (Vec2){
      .x = in.x - transformation.x,
      .y = in.y - transformation.y,
  };
}

Vec2 vec2_sub_scalar(Vec2 in, float_t transformation) {
  return (Vec2){
      .x = in.x - transformation,
      .y = in.y - transformation,
  };
}

Vec2 vec2_rotate(Vec2 in, float_t angle) {
  return (Vec2){
      .x = in.x * cos(angle) - in.y * sin(angle),
      .y = in.x * sin(angle) + in.y * cos(angle),
  };
}

Vec3 vec3_transform(Vec3 in, Vec3 transformation) {
  return (Vec3){
      .x = in.x + transformation.x,
      .y = in.y + transformation.y,
      .z = in.z + transformation.z,
  };
}

Vec3 vec3_transform_scalar(Vec3 in, float_t transformation) {
  return (Vec3){
      .x = in.x + transformation,
      .y = in.y + transformation,
      .z = in.z + transformation,
  };
}

Vec3 vec3_scale(Vec3 in, Vec3 scale) {
  return (Vec3){
      .x = in.x * scale.x,
      .y = in.y * scale.y,
      .z = in.z * scale.z,
  };
}

Vec3 vec3_scale_scalar(Vec3 in, float_t scale) {
  return (Vec3){
      .x = in.x * scale,
      .y = in.y * scale,
      .z = in.z * scale,
  };
}

Vec3 vec3_sub(Vec3 in, Vec3 transformation) {
  return (Vec3){
      .x = in.x - transformation.x,
      .y = in.y - transformation.y,
      .z = in.z - transformation.z,
  };
}

Vec3 vec3_sub_scalar(Vec3 in, float_t transformation) {
  return (Vec3){
      .x = in.x - transformation,
      .y = in.y - transformation,
      .z = in.z - transformation,
  };
}

Vec3 vec3_rotate_z(Vec3 in, float_t angle) {
  return (Vec3){
      .x = in.x * cos(angle) - in.y * sin(angle),
      .y = in.x * sin(angle) + in.y * cos(angle),
      .z = in.z,
  };
}

Vec3 vec3_rotate_y(Vec3 in, float_t angle) {
  return (Vec3){
      .x = in.x * cos(angle) - in.z * sin(angle),
      .y = in.y,
      .z = in.x * sin(angle) + in.z * cos(angle),
  };
}

Vec3 vec3_rotate_x(Vec3 in, float_t angle) {
  return (Vec3){
      .x = in.x,
      .y = in.y * cos(angle) - in.z * sin(angle),
      .z = in.y * sin(angle) + in.z * cos(angle),
  };
}