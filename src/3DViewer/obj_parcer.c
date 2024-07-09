#include "obj_parcer.h"
float parse_float_number(char* str) {
    float result = 0;
    int number_whole = 0, number_fraction = 0, count_fraction_digits = 0;
    char *tmp = str;
    int is_point = 0;
    int is_negative_number = 0;

    while (*tmp != ' ' && *tmp != '\0' && *tmp != '\n') {
        if (*tmp >= '0' && *tmp <= '9') {
            if (is_point) {
                number_fraction = number_fraction * 10 + (*tmp - '0');
                count_fraction_digits++;
            } else {
                number_whole = number_whole * 10 + (*tmp - '0');
            }
        } else if (*tmp == '.') {
            is_point = 1;
        } else if (*tmp == '-') {
            is_negative_number = 1;
        }
        tmp++;
    }

    result = (float)number_whole;
    if (count_fraction_digits > 0) {
        result += number_fraction / pow(10, count_fraction_digits);
    }
    if (is_negative_number) {
        result *= -1;
    }

    return result;
}

Vertex parse_vertex(char* str) {
    Vertex result;
    char *token;
    token = strtok(str, "v ");
    if (token != NULL) {
        result.x = parse_float_number(token);
        token = strtok(NULL, " ");
    }
    if (token != NULL) {
        result.y = parse_float_number(token);
        token = strtok(NULL, " ");
    }
    if (token != NULL) {
        result.z = parse_float_number(token);
    }
    return result;
}

Face parse_face(char* str) {
    Face result;
    char *token;
    token = strtok(str, "f ");
    if (token != NULL) {
        result.v1 = atoi(token) - 1;  // Obj indices are 1-based
        token = strtok(NULL, " ");
    }
    if (token != NULL) {
        result.v2 = atoi(token) - 1;
        token = strtok(NULL, " ");
    }
    if (token != NULL) {
        result.v3 = atoi(token) - 1;
    }
    return result;
}

int count_vertices(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        exit(1);
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            count++;
        }
    }

    fclose(file);
    return count;
}

int count_faces(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        exit(1);
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'f' && line[1] == ' ') {
            count++;
        }
    }

    fclose(file);
    return count;
}

void read_obj_file(const char *filename, Model_data *model) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        exit(1);
    }

    model->vertices = (Vertex *)malloc(model->vertex_count * sizeof(Vertex));
    if (model->vertices == NULL) {
        perror("Не удалось выделить память");
        exit(1);
    }

    model->faces = (Face *)malloc(model->face_count * sizeof(Face));
    if (model->faces == NULL) {
        perror("Не удалось выделить память");
        exit(1);
    }

    int vertex_index = 0;
    int face_index = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            char *ptr = line;
            while (*ptr == ' ' || *ptr == '\t') {
                ptr++;
            }
            model->vertices[vertex_index++] = parse_vertex(ptr);
        } else if (line[0] == 'f' && line[1] == ' ') {
            char *ptr = line;
            while (*ptr == ' ' || *ptr == '\t') {
                ptr++;
            }
            model->faces[face_index++] = parse_face(ptr);
        }
    }
    fclose(file);
}
