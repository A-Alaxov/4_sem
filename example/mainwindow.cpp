#include "mainwindow.h"
#include "main_func.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QVector3D>
#include <chrono>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

QGraphicsScene *scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->x_shift_input->setPlaceholderText(QString("x shift"));
    ui->y_shift_input->setPlaceholderText(QString("y shift"));
    ui->z_shift_input->setPlaceholderText(QString("z shift"));
    ui->x_centre_input->setPlaceholderText(QString("x centre"));
    ui->y_centre_input->setPlaceholderText(QString("y centre"));
    ui->z_centre_input->setPlaceholderText(QString("z centre"));
    ui->x_scale_input->setPlaceholderText(QString("x scale coef"));
    ui->y_scale_input->setPlaceholderText(QString("y scale coef"));
    ui->z_scale_input->setPlaceholderText(QString("z scale coef"));
    ui->xy_angle_input->setPlaceholderText(QString("xy flat angle"));
    ui->yz_angle_input->setPlaceholderText(QString("yz flat angle"));
    ui->zx_angle_input->setPlaceholderText(QString("zx flat angle"));

    scene = new QGraphicsScene();
}

MainWindow::~MainWindow() {
    delete scene;

    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    parametrs par;

    main_func(SHOW, par);

    draw();
}

void MainWindow::on_shift_button_clicked() {
    parametrs par;

    par.shift.x_shift = ui->x_shift_input->text().toDouble();
    par.shift.y_shift = ui->y_shift_input->text().toDouble();
    par.shift.z_shift = ui->z_shift_input->text().toDouble();

    main_func(SHIFT, par);

    draw();
}

void MainWindow::on_rotate_button_clicked() {
    parametrs par;

    par.rotate.centre.x = ui->x_centre_input->text().toDouble();
    par.rotate.centre.y = ui->y_centre_input->text().toDouble();
    par.rotate.centre.z = ui->z_centre_input->text().toDouble();

    par.rotate.xy_angle = ui->xy_angle_input->text().toDouble();
    par.rotate.yz_angle = ui->yz_angle_input->text().toDouble();
    par.rotate.zx_angle = ui->zx_angle_input->text().toDouble();

    main_func(ROTATE, par);

    draw();
}

void MainWindow::on_scale_button_clicked() {
    parametrs par;

    par.scale.centre.x = ui->x_centre_input->text().toDouble();
    par.scale.centre.y = ui->y_centre_input->text().toDouble();
    par.scale.centre.z = ui->z_centre_input->text().toDouble();

    par.scale.x_scale = ui->x_scale_input->text().toDouble();
    par.scale.y_scale = ui->y_scale_input->text().toDouble();
    par.scale.z_scale = ui->z_scale_input->text().toDouble();

    main_func(SCALE, par);

    draw();
}

void MainWindow::draw() {
    ui->graphicsView->items().clear();
    QImage image = QImage(600, 600, QImage::Format_RGB32);
    QPainter p(&image);

    p.setBrush(QColor(0, 0, 0));
    p.setPen(QColor(200, 0, 0));

    parametrs edge;
    int rc = OK;

    for (size_t i = 0; rc == OK; i++) {
        edge.edge.number = i;
        rc = main_func(GET_EDGE, edge);

        if (!rc)
            p.drawLine(edge.edge.edge.dot1.x, edge.edge.edge.dot1.y, edge.edge.edge.dot2.x, edge.edge.edge.dot2.y);
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_MainWindow_destroyed() {}
