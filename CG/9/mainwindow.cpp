#include <QColorDialog>
#include <QMessageBox>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cut_col->set_color(cut_col);
    ui->seg_col->set_color(seg_col);
    ui->vis_part_col->set_color(vis_col);

    ui->field->set_cut_col(ui->cut_col->get_color());
    ui->field->set_vis_col(ui->vis_part_col->get_color());
    ui->field->set_seg_col(ui->seg_col->get_color());
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

    ui->field->set_seg_col(dialog.selectedColor());
}

void MainWindow::on_vis_part_col_btn_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->vis_part_col->set_color(dialog.selectedColor());

    ui->field->set_vis_col(dialog.selectedColor());
}

void MainWindow::on_cut_col_btn_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->cut_col->set_color(dialog.selectedColor());

    ui->field->set_cut_col(dialog.selectedColor());
}

void MainWindow::on_pushButton_clicked()
{
    bool conv = ui->field->cut();
    if (!conv)
    {
        QMessageBox msg;
        msg.setText("Ошибка! Отсекатель не является выпуклым");
        msg.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->field->clear();
}

void MainWindow::on_end_cutter_clicked()
{
    ui->field->end_cutter();
}

void MainWindow::on_end_enter_clicked()
{
    ui->field->end_enter();
}
