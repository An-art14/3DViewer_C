#pragma once
#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H
typedef struct {
    float x, y, z;
} Vertex;

// Структура для хранения данных модели
typedef struct {
    Vertex *vertices;   // Указатель на массив вершин
    int vertex_count;   // Количество вершин
} Model_data;


#endif // OBJ_MODEL_H
