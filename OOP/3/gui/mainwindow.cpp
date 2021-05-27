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
#include "drawer_solution.hpp"

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
    ui->file_name->setPlaceholderText(QString("file name for model"));
    ui->file_name_camera->setPlaceholderText(QString("file name for camera"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shift_fig_clicked()
{
    long index = ui->model_select->currentIndex();
    point shift(ui->x_shift_fig->text().toDouble(), ui->y_shift_fig->text().toDouble(), ui->z_shift_fig->text().toDouble());
    point scale(1, 1, 1);
    point rotate(0, 0, 0);
    std::shared_ptr<base_command> command(new reform_model(index, shift, scale, rotate));
    _facade->execute_command(command);

    update_scene();
}

void MainWindow::on_rotate_fig_clicked()
{
    long index = ui->model_select->currentIndex();
    point shift(0, 0, 0);
    point scale(1, 1, 1);
    point rotate(ui->xy_angle_fig->text().toDouble(), ui->yz_angle_fig->text().toDouble(), ui->zx_angle_fig->text().toDouble());
    std::shared_ptr<base_command> command(new reform_model(index, shift, scale, rotate));
    _facade->execute_command(command);

    update_scene();
}

void MainWindow::on_scale_fig_clicked()
{
    long index = ui->model_select->currentIndex();
    point shift(0, 0, 0);
    point scale(ui->x_scale_fig->text().toDouble(), ui->y_scale_fig->text().toDouble(), ui->z_scale_fig->text().toDouble());
    point rotate(0, 0, 0);
    std::shared_ptr<base_command> command(new reform_model(index, shift, scale, rotate));
    _facade->execute_command(command);

    update_scene();
}

void MainWindow::on_import_fig_clicked()
{
    std::shared_ptr<base_command> command(new load_model(ui->file_name->text().toStdString()));
    try
    {
        _facade->execute_command(command);
        ui->model_select->addItem(QString::number(ui->model_select->count()));
        ui->model_select->setCurrentIndex(ui->model_select->count() - 1);

        update_scene();
    }
    catch (base_error &er)
    {
        print_message(er.get_info());
    }
}

void MainWindow::draw()
{
}

void MainWindow::print_message(std::string str)
{
    QMessageBox msg;
    msg.setText(QString().fromUtf8(str.c_str()));
    msg.exec();
}

void MainWindow::on_add_cam_clicked()
{
    std::shared_ptr<base_command> command(new load_camera(ui->file_name_camera->text().toStdString()));
    _facade->execute_command(command);
    ui->camera_select->addItem(QString::number(ui->camera_select->count()));
    ui->camera_select->setCurrentIndex(ui->camera_select->count() - 1);

    update_scene();
}

void MainWindow::on_shift_cam_clicked()
{
    long index = ui->camera_select->currentIndex();
    point shift(ui->x_shift_cam->text().toDouble(), ui->y_shift_cam->text().toDouble(), ui->z_shift_cam->text().toDouble());
    point rotate(0, 0, 0);
    std::shared_ptr<base_command> command(new reform_camera(index, shift, rotate));
    _facade->execute_command(command);

    update_scene();
}

void MainWindow::on_rotate_cam_clicked()
{
    long index = ui->camera_select->currentIndex();
    point shift(0, 0, 0);
    point rotate(ui->xy_angle_cam->text().toDouble(), ui->yz_angle_cam->text().toDouble(), ui->zx_angle_cam->text().toDouble());
    std::shared_ptr<base_command> command(new reform_camera(index, shift, rotate));
    _facade->execute_command(command);

    update_scene();
}

void MainWindow::setup_scene()
{
/*
    scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene(this));
    ui->graphicsView->setScene(scene.get());
*/

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    std::shared_ptr<abstract_factory> factory = drawer_solution().get_factory();
    drawer = std::shared_ptr<base_drawer>(factory->create_ui());
    drawer->set_canvas(std::make_shared<qt_canvas>(scene));
}

void MainWindow::update_scene()
{
    std::shared_ptr<base_command> command(new draw_scene(drawer));
    _facade->execute_command(command);
}

void MainWindow::on_MainWindow_destroyed() {}

void MainWindow::on_remove_fig_clicked()
{
    long index = ui->model_select->currentIndex();
    std::shared_ptr<base_command> command(new remove_model(index));
    _facade->execute_command(command);
    ui->model_select->removeItem(index);

    update_scene();
}

void MainWindow::on_remove_cam_clicked()
{
    long index = ui->camera_select->currentIndex();
    std::shared_ptr<base_command> command(new remove_camera(index));
    _facade->execute_command(command);
    ui->camera_select->removeItem(index);

    update_scene();
}

void MainWindow::on_camera_select_currentIndexChanged(int index)
{
    std::shared_ptr<base_command> command(new set_camera(index));
    _facade->execute_command(command);

    update_scene();
}
