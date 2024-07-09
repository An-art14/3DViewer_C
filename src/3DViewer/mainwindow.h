#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <gif.h>
#include <QMainWindow>
extern "C" {
#include "obj_parcer.h"
}
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isRecording() const ;
    GifWriter& getGifWriter();
private slots:
    void on_FileButton_clicked();


    void on_xTransitionSlider_valueChanged(int value);

    void on_xTransitionSpinBox_valueChanged(double arg1);

    void on_yTransitionSlider_valueChanged(int value);

    void on_yTransitionSpinBox_valueChanged(double arg1);

    void on_zTransitionSlider_valueChanged(int value);

    void on_zTransitionSpinBox_valueChanged(double arg1);

    void on_xRotationSlider_valueChanged(int value);

    void on_xRotationSpinBox_valueChanged(double arg1);

    void on_yRotationSlider_valueChanged(int value);

    void on_yRotationSpinBox_valueChanged(double arg1);

    void on_zRotationSlider_valueChanged(int value);

    void on_zRotationSpinBox_valueChanged(double arg1);

    void on_ScaleSlider_valueChanged(int value);

    void on_ScaleSpinBox_valueChanged(double arg1);

    void on_ScrenshotButton_clicked();

    void on_GifButton_clicked();

private:
    Ui::MainWindow *ui;
    Model_data model;
    void draw();
    void transformAndDraw();
    bool recording;
    GifWriter gifWriter;
    void startRecording();
    void stopRecording();
};
#endif // MAINWINDOW_H
