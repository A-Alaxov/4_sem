#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <QMouseEvent>
#include <QKeyEvent>

#include "figure.h"

class canvas : public QWidget
{
    Q_OBJECT

public:
    explicit canvas(QWidget *parent = nullptr);
    ~canvas();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void finish_figure();
    void add_hole();

    void get_time(double &time);

    void clear();

    void set_bg(const QColor &color);
    void set_fg(const QColor &color);
    void set_paint_col(const QColor &color);

    void set_delay(size_t delay);
    void set_hor();
    void set_ver();
    void set_seed();

    void add_point(int x, int y);

private:
    void redraw();
    QImage *image = nullptr;

    std::vector<figure *> figures;

    point seed_p;

    QColor bg;
    QColor fg;
    QColor paint_col;

    size_t delay = 0;

    bool finished = true;
    bool horizontal = false;
    bool vertical = false;
    bool seed = false;
};

#endif // CANVAS_H
