#include "obj_parcer.h"

void move_x(Model_data* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[3 * i] += value;
  }
}

void move_y(Model_data* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[3 * i + 1] += value;
  }
}

void move_z(Model_data* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[3 * i + 2] += value;
  }
}

void rotate_x(Model_data* obj, float angle) {
  for (int i = 0; i < obj->vertex_count * 3; i += 3) {
    double y = obj->vertices[i + 1];
    double z = obj->vertices[i + 2];
    obj->vertices[i + 1] = y * cos(angle) - z * sin(angle);
    obj->vertices[i + 2] = y * sin(angle) + z * cos(angle);
  }
}
void rotate_y(Model_data* obj, float angle) {
  for (int i = 0; i < obj->vertex_count * 3; i += 3) {
    double x = obj->vertices[i];
    double z = obj->vertices[i + 2];
    obj->vertices[i] = cos(angle) * x + sin(angle) * z;
    obj->vertices[i + 2] = cos(angle) * z - sin(angle) * x;
  }
}

void rotate_z(Model_data* obj, float angle) {
  for (int i = 0; i < obj->vertex_count * 3; i += 3) {
    double x = obj->vertices[i];
    double y = obj->vertices[i + 1];
    obj->vertices[i] = cos(angle) * x - sin(angle) * y;
    obj->vertices[i + 1] = cos(angle) * y + sin(angle) * x;
  }
}

void scale(Model_data* obj, float ratio) {
  if (ratio > 0) {
    for (int i = 0; i < (obj->vertex_count) * 3; i++) {
      obj->vertices[i] *= ratio;
    }
  }
}