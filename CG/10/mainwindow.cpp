#include <QColorDialog>
#include <QMessageBox>

#include "mainwindow.hpp"
#include "funcs.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->seg_col->set_color(bg);
    ui->vis_part_col->set_color(fg);

    ui->field->set_bg(ui->seg_col->get_color());
    ui->field->set_fg(ui->vis_part_col->get_color());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_seg_col_btn_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->seg_col->set_color(dialog.selectedColor());

    ui->field->set_bg(dialog.selectedColor());
}

void MainWindow::on_vis_part_col_btn_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->vis_part_col->set_color(dialog.selectedColor());

    ui->field->set_fg(dialog.selectedColor());
}

void MainWindow::on_cut_col_btn_clicked()
{
}

void MainWindow::on_pushButton_clicked()
{
    double (*f)(double x, double z);
    if (ui->comboBox->currentIndex() == 0)
        f = func3;
    else if (ui->comboBox->currentIndex() == 1)
        f = func4;
    else if (ui->comboBox->currentIndex() == 2)
        f = func2;
    else
        f = func1;
    ui->field->draw(f, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->field->clear();
}

void MainWindow::on_end_cutter_clicked()
{
    ui->field->set_scale(ui->scale->text().toDouble());
    double (*f)(double x, double z);
    if (ui->comboBox->currentIndex() == 0)
        f = func3;
    else if (ui->comboBox->currentIndex() == 1)
        f = func4;
    else if (ui->comboBox->currentIndex() == 2)
        f = func2;
    else
        f = func1;
    ui->field->draw(f, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}

void MainWindow::on_end_enter_clicked()
{
    ui->field->rotate_x(ui->angle_x->text().toDouble());
    double (*f)(double x, double z);
    if (ui->comboBox->currentIndex() == 0)
        f = func3;
    else if (ui->comboBox->currentIndex() == 1)
        f = func4;
    else if (ui->comboBox->currentIndex() == 2)
        f = func2;
    else
        f = func1;
    ui->field->draw(f, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}

void MainWindow::on_rotate_y_clicked()
{
    ui->field->rotate_y(ui->angle_y->text().toDouble());
    double (*f)(double x, double z);
    if (ui->comboBox->currentIndex() == 0)
        f = func3;
    else if (ui->comboBox->currentIndex() == 1)
        f = func4;
    else if (ui->comboBox->currentIndex() == 2)
        f = func2;
    else
        f = func1;
    ui->field->draw(f, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}

void MainWindow::on_rotate_z_clicked()
{
    ui->field->rotate_z(ui->angle_z->text().toDouble());
    double (*f)(double x, double z);
    if (ui->comboBox->currentIndex() == 0)
        f = func3;
    else if (ui->comboBox->currentIndex() == 1)
        f = func4;
    else if (ui->comboBox->currentIndex() == 2)
        f = func2;
    else
        f = func1;
    ui->field->draw(f, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}
