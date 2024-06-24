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
// Функция для подсчета количества вершин в файле Obj
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


// Функция для чтения данных из файла Obj
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

    int index = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            // Убираем лишние пробелы в начале строки
            char *ptr = line;
            while (*ptr == ' ' || *ptr == '\t') {
                ptr++;
            }


            Vertex vertex;
            vertex=parse_vertex(ptr);
            model->vertices[index++] = vertex;

        }
    }
    fclose(file);
}
