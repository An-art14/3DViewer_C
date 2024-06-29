#include "obj_parcer.h"

void move_x(Model_data* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[i].x += value;
  }
}

void move_y(Model_data* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[i].y += value;
  }
}

void move_z(Model_data* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[i].z += value;
  }
}

void rotate_x(Model_data* obj, float angle) {
  for (int i = 0; i < obj->vertex_count; i++) {
    double y = obj->vertices[i].y;
    double z = obj->vertices[i].z;
    obj->vertices[i].y = y * cos(angle) - z * sin(angle);
    obj->vertices[i].z = y * sin(angle) + z * cos(angle);
  }
}

void rotate_y(Model_data* obj, float angle) {
  for (int i = 0; i < obj->vertex_count; i++) {
    double x = obj->vertices[i].x;
    double z = obj->vertices[i].z;
    obj->vertices[i].x = cos(angle) * x + sin(angle) * z;
    obj->vertices[i].z = cos(angle) * z - sin(angle) * x;
  }
}

void rotate_z(Model_data* obj, float angle) {
  for (int i = 0; i < obj->vertex_count; i++) {
    double x = obj->vertices[i].x;
    double y = obj->vertices[i].y;
    obj->vertices[i].x = cos(angle) * x - sin(angle) * y;
    obj->vertices[i].y = cos(angle) * y + sin(angle) * x;
  }
}

void scale(Model_data* obj, float ratio) {
  if (ratio > 0) {
    for (int i = 0; i < obj->vertex_count; i++) {
      obj->vertices[i].x *= ratio;
      obj->vertices[i].y *= ratio;
      obj->vertices[i].z *= ratio;
    }
  }
}
