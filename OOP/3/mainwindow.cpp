#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QVector3D>
#include <QMessageBox>
#include <chrono>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drawer_factory.hpp"

QGraphicsScene *scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _facade(new facade)
{
    ui->setupUi(this);
    setup_scene();

    ui->x_shift_fig->setPlaceholderText(QString("x shift"));
    ui->y_shift_fig->setPlaceholderText(QString("y shift"));
    ui->z_shift_fig->setPlaceholderText(QString("z shift"));
    ui->x_scale_fig->setPlaceholderText(QString("x scale coef"));
    ui->y_scale_fig->setPlaceholderText(QString("y scale coef"));
    ui->z_scale_fig->setPlaceholderText(QString("z scale coef"));
    ui->xy_angle_fig->setPlaceholderText(QString("xy flat angle"));
    ui->yz_angle_fig->setPlaceholderText(QString("yz flat angle"));
    ui->zx_angle_fig->setPlaceholderText(QString("zx flat angle"));
    ui->x_shift_cam->setPlaceholderText(QString("x shift"));
    ui->y_shift_cam->setPlaceholderText(QString("y shift"));
    ui->z_shift_cam->setPlaceholderText(QString("z shift"));
    ui->xy_angle_cam->setPlaceholderText(QString("xy flat angle"));
    ui->yz_angle_cam->setPlaceholderText(QString("yz flat angle"));
    ui->zx_angle_cam->setPlaceholderText(QString("zx flat angle"));
    ui->file_name->setPlaceholderText(QString("file name"));
}

MainWindow::~MainWindow()
{
    delete scene;

    delete ui;
}

void MainWindow::on_shift_fig_clicked()
{
}

void MainWindow::on_rotate_fig_clicked()
{
}

void MainWindow::on_scale_fig_clicked()
{
}

void MainWindow::on_import_fig_clicked()
{
    std::shared_ptr<base_command> command(new load_model(ui->file_name->text().toStdString()));
    _facade->execute_command(command);

    update_scene();
}

void MainWindow::draw()
{
}

void MainWindow::print_message(char *str)
{
    QMessageBox msg;
    msg.setText(QString(str));
    msg.exec();
}

void MainWindow::on_add_cam_clicked()
{
}

void MainWindow::on_shift_cam_clicked()
{
}

void MainWindow::on_rotate_cam_clicked()
{
}

void MainWindow::setup_scene()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, 900, 600);

    std::shared_ptr<abstract_factory> factory(new qt_factory);
    std::shared_ptr<base_drawer> _drawer(new qt_drawer(scene));
    drawer = _drawer;
}

void MainWindow::update_scene()
{
    std::shared_ptr<base_command> command(new draw_scene(drawer));
    _facade->execute_command(command);
}

void MainWindow::on_MainWindow_destroyed() {}
