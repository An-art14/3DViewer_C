#include "obj_parcer.h"

int create_obj(object_t *obj) {
    int code = OK;
    obj->faces = NULL;
    obj->points = NULL;
    obj->num_vertices = 0;
    obj->num_faces = 0;
    obj->line_num = 0;
    return code;
}

int add_vertex_to_obj(object_t *obj, double *coord) {
    int code = OK;
    obj->points[obj->num_vertices].x = coord[0];
    obj->points[obj->num_vertices].y = coord[1];
    obj->points[obj->num_vertices].z = coord[2];
    obj->num_vertices++;
    return code;
}

int add_face_to_obj(object_t *obj, unsigned *indices, int num_indices) {
    obj->faces[obj->num_faces].vertex_indices = malloc(num_indices * sizeof(unsigned));
    if (obj->faces[obj->num_faces].vertex_indices == NULL) {
        return ERROR;
    }

    obj->faces[obj->num_faces].num_indices_in_face = num_indices;
    for (int i = 0; i < num_indices; i++) {
        obj->faces[obj->num_faces].vertex_indices[i] = indices[i];
    }
    obj->num_faces++;

    return OK;
}

int write_coord_vertex(char *line, object_t *obj) {
    int code = OK;
    double x = 0.0, y = 0.0, z = 0.0;
    if (sscanf(line, "v %lf %lf %lf", &x, &y, &z) == 3) {
        double coord[3] = {x, y, z};
        code = add_vertex_to_obj(obj, coord);
        if (code != OK) {
            return ERROR;
        }
    }
    return code;
}

int is_digit(char c) {
    return isdigit(c);
}

int count_faces(FILE *file) {
    int num_faces = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'f') {
            num_faces++;
        }
    }

    rewind(file); // Возвращаемся к началу файла

    return num_faces;
}

int count_vertices(FILE *file) {
    int num_vertices = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            num_vertices++;
        }
    }

    rewind(file); // Возвращаемся к началу файла

    return num_vertices;
}

int allocate_faces(object_t *obj, int num_faces) {
    obj->faces = calloc(num_faces, sizeof(face_t));
    if (obj->faces == NULL) {
        return ERROR;
    }
    obj->num_faces = 0;
    return OK;
}

int allocate_vertices(object_t *obj, int num_vertices) {
    obj->points = calloc(num_vertices, sizeof(vertex_t));
    if (obj->points == NULL) {
        return ERROR;
    }
    obj->num_vertices = 0;
    return OK;
}

int write_ind_vertices(char *line, object_t *obj) {
    int code = OK;
       unsigned indices[100];
       int num_indices = 0;
       char *p = line + 2;

       while (*p != '\0' && num_indices < 100) {
           if (is_digit(*p)) {
               if (sscanf(p, "%u", &indices[num_indices]) != 1) {
                   return ERROR;
               }
               num_indices++;
               while (is_digit(*p)) {
                   p++;
               }
           }
           if (*p != '\0') {
               p++;
           }
       }
       if (num_indices == 0) {
           return ERROR;
       }
       code = add_face_to_obj(obj, indices, num_indices);
       return code;
}

void clean_obj(object_t *obj) {

if(obj->num_faces!=0){
        for (int i = 0; i < obj->num_faces; i++) {
            if(obj->faces[i].vertex_indices!=NULL){
            free(obj->faces[i].vertex_indices);
            }
        }
}
if(obj->faces!=NULL){
        free(obj->faces);
}
if(obj->points!=NULL){
        free(obj->points);
}

}

int parse_obj_file(const char *filename, object_t *obj) {
    int code = OK;
    size_t len = 0;
    char *line = NULL;
    FILE *fp = fopen(filename, "r");

    if (fp == NULL || obj == NULL) {
        return ERROR;
    }

    // Первый проход для подсчета количества вершин и граней
    int num_vertices = count_vertices(fp);
    int num_faces = count_faces(fp);

    // Выделение памяти для вершин и граней
    if (allocate_vertices(obj, num_vertices) != OK || allocate_faces(obj, num_faces) != OK) {
        fclose(fp);
        return ERROR;
    }

    // Второй проход для загрузки данных
    while (getline(&line, &len, fp) != -1) {
        if (line[0] == 'v' && line[1] == ' ') {
            write_coord_vertex(line, obj);
        } else if (line[0] == 'f' && line[1] == ' ') {
            write_ind_vertices(line, obj);
        }
        free(line);
        line = NULL;
        len = 0;
    }

    obj->line_num = obj->num_faces + obj->num_vertices - 2;

    free(line);
    fclose(fp);
    return code;
}
