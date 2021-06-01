#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "figures.hpp"
#include "cutter.hpp"

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget *parent = nullptr);
    ~canvas();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void clear();
    void set_bg(const QColor &color);
    void set_seg_col(const QColor &color);
    void set_vis_col(const QColor &color);
    void set_cut_col(const QColor &color);
    long cut();
    void end_cutter();
    void end_enter();

private:
    QColor bg = QColor(255, 255, 255);
    cutter _cutter = cutter(QColor(0, 0, 0), QColor(0, 0, 0), QColor(0, 0, 0));
    bool process = false;

signals:

};

#endif // CANVAS_HPP
