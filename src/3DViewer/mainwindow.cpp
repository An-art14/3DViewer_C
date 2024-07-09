#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"widget.h"
#include<QFileDialog>
#include<QDebug>
#include"obj_parcer.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      recording(false)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                            tr("Open OBJ File"),
                                                            "",
                                                            tr("OBJ Files (*.obj)"));
            if (!fileName.isEmpty()) {
                qDebug() << "Selected file:" << fileName;

                ui->openGLWidget->makeCurrent();
                        ui->openGLWidget->draw_obj(fileName.toStdString().c_str());
                        ui->openGLWidget->update();  // Ensure the widget is repainted
                        ui->PathLabel->setText("Path:"+fileName);
                        model=ui->openGLWidget->getModel();
                        QString vertexStr = "vertex: " + QString::number(model.vertex_count);
                        ui->VertexLabel->setText(vertexStr);

                        QString faceStr = "face: " + QString::number(model.face_count);
                        ui->FacetesLabel->setText(faceStr);
            } else {
                qDebug() << "No file selected.";
            }
}

void MainWindow::draw()
{
    ui->openGLWidget->makeCurrent();
ui->openGLWidget->draw(model);
ui->openGLWidget->update();  // Ensure the widget is repainted
}

void MainWindow::transformAndDraw()
{
     ui->openGLWidget->makeCurrent();
     ui->openGLWidget->draw(model);
     ui->openGLWidget->update();
}
void MainWindow::on_xTransitionSlider_valueChanged(int value)
{
    ui->xTransitionSpinBox->setValue(value);
    move_x(&model, value);
    transformAndDraw();
}

void MainWindow::on_xTransitionSpinBox_valueChanged(double arg1)
{
    ui->xTransitionSlider->setValue(arg1);
    move_x(&model, arg1);
    transformAndDraw();
}

void MainWindow::on_yTransitionSlider_valueChanged(int value)
{
    ui->yTransitionSpinBox->setValue(value);
    move_y(&model, value);
    transformAndDraw();
}

void MainWindow::on_yTransitionSpinBox_valueChanged(double arg1)
{
    ui->yTransitionSlider->setValue(arg1);
    move_y(&model, arg1);
    transformAndDraw();
}

void MainWindow::on_zTransitionSlider_valueChanged(int value)
{
    ui->zTransitionSpinBox->setValue(value);
    move_z(&model, value);
    transformAndDraw();
}

void MainWindow::on_zTransitionSpinBox_valueChanged(double arg1)
{
    ui->zTransitionSlider->setValue(arg1);
    move_z(&model, arg1);
    transformAndDraw();
}

void MainWindow::on_xRotationSlider_valueChanged(int value)
{
    ui->xRotationSpinBox->setValue(value);
    rotate_x(&model, value);
    transformAndDraw();
}

void MainWindow::on_xRotationSpinBox_valueChanged(double arg1)
{
    ui->xRotationSlider->setValue(arg1);
    rotate_x(&model, arg1);
    transformAndDraw();
}

void MainWindow::on_yRotationSlider_valueChanged(int value)
{
    ui->yRotationSpinBox->setValue(value);
    rotate_y(&model, value);
    transformAndDraw();
}

void MainWindow::on_yRotationSpinBox_valueChanged(double arg1)
{
    ui->yRotationSlider->setValue(arg1);
    rotate_y(&model, arg1);
    transformAndDraw();
}

void MainWindow::on_zRotationSlider_valueChanged(int value)
{
    ui->zRotationSpinBox->setValue(value);
    rotate_z(&model, value);
    transformAndDraw();
}

void MainWindow::on_zRotationSpinBox_valueChanged(double arg1)
{
    ui->zRotationSlider->setValue(arg1);
    rotate_z(&model, arg1);
    transformAndDraw();
}

void MainWindow::on_ScaleSlider_valueChanged(int value)
{
    ui->ScaleSpinBox->setValue(value);
    scale(&model, value / 100.0); // Assuming the slider value is in percentage (0-100)
    transformAndDraw();
    qDebug()<<"test";
}

void MainWindow::on_ScaleSpinBox_valueChanged(double arg1)
{
    ui->ScaleSlider->setValue(arg1);
    scale(&model, arg1);
    transformAndDraw();
}

void MainWindow::on_ScrenshotButton_clicked()
{
    QImage screenshot = ui->openGLWidget->grabFramebuffer();


        QString filter = "BMP files (*.bmp);;JPEG files (*.jpg)";
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Screenshot"), "", filter);

        if (!fileName.isEmpty()) {

            QFileInfo fileInfo(fileName);
            QString extension = fileInfo.suffix().toLower();

            if (extension == "bmp") {
                screenshot.save(fileName, "BMP");
            } else if (extension == "jpg" || extension == "jpeg") {
                screenshot.save(fileName, "JPEG");
            } else {

                screenshot.save(fileName + ".jpg", "JPEG");
            }
        }
}


void MainWindow::on_GifButton_clicked()
{
    if (!recording) {
        startRecording();
    } else {
        stopRecording();
    }
}
void MainWindow::startRecording()
{
    // Меняем текст кнопки на "Save"
    ui->GifButton->setText("Save");
    recording = true;

    // Начало записи GIF
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save GIF"), "", tr("GIF files (*.gif)"));
    if (!fileName.isEmpty()) {
        GifBegin(&gifWriter, fileName.toStdString().c_str(), 640, 480, 10);
    }
}

void MainWindow::stopRecording()
{
    // Останавливаем запись GIF
    GifEnd(&gifWriter);
    recording = false;

    // Меняем текст кнопки обратно
    ui->GifButton->setText("Start GIF Recording");
}
bool MainWindow::isRecording() const { return recording; }
GifWriter&  MainWindow::getGifWriter() { return gifWriter; }
