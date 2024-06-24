#include "widget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QDebug>
#include <GLES3/gl3.h>
#include<math.h>
#include "obj_parcer.h"
Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

Widget::~Widget()
{
    makeCurrent();
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &vboIndices);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
    doneCurrent();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    draw_obj("cube.obj");
    setupShader();

}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Widget::paintGL()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Bind VAO and draw the rectangle
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // Unbind VAO

    // Optional: Cleanup state
    glUseProgram(0);
}






void Widget::draw_obj(const char* filename)
{


    // Считаем количество вершин в файле
    int vertex_count =  count_vertices(filename);
    // Структура для хранения данных модели
    Model_data model;
    model.vertex_count = vertex_count;

    // Чтение данных из файла cube.obj
    read_obj_file(filename, &model);

    // Преобразование данных модели в формат, пригодный для OpenGL
    std::vector<float> vertices;
    for (int i = 0; i < model.vertex_count; ++i) {
        vertices.push_back(model.vertices[i].x);
        vertices.push_back(model.vertices[i].y);
        vertices.push_back(model.vertices[i].z);

    }

    free(model.vertices);

    // Индексы вершин для отрисовки куба (оставляем без изменений)
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 4, 7,
        7, 3, 0,
        1, 5, 6,
        6, 2, 1,
        0, 1, 5,
        5, 4, 0,
        2, 3, 7,
        7, 6, 2
    };

    // Генерация и привязка VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Генерация и заполнение буфера вершин
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Установка указателей на атрибуты вершин
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


//    // Генерация и заполнение индексного буфера
    glGenBuffers(1, &vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

//    // Отвязка VAO
    glBindVertexArray(0);
    numIndices=indices.size();// Число индексов в кубе



}


void Widget::setupShader()
{
    // Vertex shader source code
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        out vec4 fragColor;

        uniform mat4 u_MVP;
        uniform vec4 u_Color;

        void main(void) {
            gl_Position = u_MVP * vec4(position, 1.0);
            fragColor = u_Color;
        }
    )";

    // Fragment shader source code
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec4 fragColor;
        out vec4 color;

        void main(void) {
            color = fragColor;
        }
    )";

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for shader linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use the shader program and set the color to blue
    glUseProgram(shaderProgram);
    GLint colorLocation = glGetUniformLocation(shaderProgram, "u_Color");
    if (colorLocation != -1) {
        glUniform4f(colorLocation, 0.0f, 0.0f, 1.0f, 1.0f); // Set color to blue
    } else {
        qDebug() << "ERROR::SHADER::UNIFORM::COLOR_LOCATION_NOT_FOUND";
    }

    // Set MVP matrix (for simplicity, we use identity matrix)
    GLint mvpLocation = glGetUniformLocation(shaderProgram, "u_MVP");
    if (mvpLocation != -1) {
        QMatrix4x4 mvp;
        mvp.setToIdentity();
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.constData());
    } else {
        qDebug() << "ERROR::SHADER::UNIFORM::MVP_LOCATION_NOT_FOUND";
    }
}

void Widget::clearCanvas()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}
