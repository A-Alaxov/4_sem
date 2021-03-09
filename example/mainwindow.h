#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_MainWindow_destroyed();

  void on_shift_button_clicked();

  void on_scale_button_clicked();

  void on_rotate_button_clicked();

private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;

  void draw();
};
#endif // MAINWINDOW_H
