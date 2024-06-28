#pragma once
#ifndef OBJ_PARCER_H
#define OBJ_PARCER_H

#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<math.h>
#include"obj_model.h"

/*
#include <ctype.h>
#include <locale.h>
*/


int count_vertices(const char *filename) ;
float parse_float_number(char* str);
Vertex parse_vertex(char* str);
void read_obj_file(const char *filename, Model_data *model);

void move_x(Model_data* obj, float value);
void move_y(Model_data* obj, float value);
void move_z(Model_data* obj, float value);
void rotate_x(Model_data* obj, float angle);
void rotate_y(Model_data* obj, float angle);
void rotate_z(Model_data* obj, float angle);
void scale(Model_data* obj, float ratio);


#endif // OBJ_PARCER_H
