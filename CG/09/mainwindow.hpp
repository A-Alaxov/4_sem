#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QColor>
#include "canvas.hpp"

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

private:
    Ui::MainWindow *ui;
    QColor seg_col = QColor(0, 255, 0);
    QColor vis_col = QColor(0, 0, 255);
    QColor cut_col = QColor(0, 0, 0);
};
#endif // MAINWINDOW_HPP
