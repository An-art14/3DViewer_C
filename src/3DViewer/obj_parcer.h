#pragma once
#ifndef OBJ_PARCER_H
#define OBJ_PARCER_H

#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<math.h>
#include"obj_model.h"


int count_vertices(const char *filename) ;
float parse_float_number(char* str);
Vertex parse_vertex(char* str);
void read_obj_file(const char *filename, Model_data *model);
#endif // OBJ_PARCER_H
