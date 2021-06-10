#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QColor>
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_seg_col_btn_clicked();

    void on_vis_part_col_btn_clicked();

    void on_cut_col_btn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_end_cutter_clicked();

    void on_end_enter_clicked();

    void on_rotate_y_clicked();

    void on_rotate_z_clicked();

private:
    Ui::MainWindow *ui;
    QColor bg = QColor(255, 255, 255);
    QColor fg = QColor(0, 0, 0);
};
#endif // MAINWINDOW_HPP
