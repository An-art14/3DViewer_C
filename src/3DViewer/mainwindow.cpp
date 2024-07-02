#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"widget.h"
#include<QFileDialog>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
                ui->openGLWidget->clearCanvas();
                ui->openGLWidget->draw_obj(fileName.toStdString().c_str());
                //ui->openGLWidget->setupShader();

            } else {
                qDebug() << "No file selected.";
            }
}

