#pragma once
#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H
typedef struct {
    float x, y, z;
} Vertex;
typedef struct {
    unsigned int v1, v2, v3;
} Face;

// Структура для хранения данных модели
typedef struct {
    Vertex* vertices;
    int vertex_count;
    Face* faces;
    int face_count;
} Model_data;


#endif // OBJ_MODEL_H
