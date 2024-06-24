#ifndef WIDGET_H
#define WIDGET_H
extern "C" {
#include "obj_parcer.h"
}

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void draw_obj(const char * filename);
    void setupShader();
    void clearCanvas();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:



    GLuint vao;
    GLuint vboVertices;
GLuint vboTexCoords;
    GLuint vboIndices;
    GLuint shaderProgram;
    int numIndices;
};

#endif // WIDGET_H
