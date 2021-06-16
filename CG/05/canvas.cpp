#include <iostream>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include "canvas.h"

canvas::canvas(QWidget *parent)
    : QWidget(parent)
{
}

canvas::~canvas()
{
    delete image;
    for (polygon *f : shapes)
        delete f;
    shapes.clear();
}

void canvas::set_bg(const QColor &color)
{
    bg = color;
}

void canvas::set_fg(const QColor &color)
{
    fg = color;
}

void canvas::set_paint_col(const QColor &color)
{
    paint_col = color;
}

void canvas::redraw()
{
    if (!image)
        image = new QImage(this->width(), this->height(), QImage::Format_RGB32);
    QPainter painter(image);

    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(bg);
    painter.drawRect(0, 0, this->width(), this->height());

    if (finished)
    {
        for(polygon *p : shapes)
            p->draw(painter);

        for (polygon * p : shapes)
            p->paint(painter, image, delay, this, bg);
    }

    for(polygon *p : shapes)
        p->draw(painter);

    update();
}

void canvas::paintEvent(QPaintEvent *event)
{
    if (!image)
        image = new QImage(this->width(), this->height(), QImage::Format_RGB32);

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.drawImage(0, 0, *image);
}

void canvas::add_point(int x, int y)
{
    point *p = new point(x, y);

    if (finished)
    {
        polygon *pol = new polygon(fg, paint_col);
        pol->add_point(p, false, false);
        shapes.push_back(pol);
        finished = false;
    }
    else
    {
        shapes.back()->add_point(p, horizontal, vertical);
        horizontal = false;
        vertical = false;
    }

    redraw();
}

void canvas::mousePressEvent(QMouseEvent *event)
{
    add_point((long) event->pos().x(), (long) event->pos().y());
}

void canvas::finish_figure()
{
    if (!shapes.size())
        return;
    shapes.back()->close();
    finished = true;

    redraw();
}

void canvas::add_hole()
{
    shapes.back()->add_hole();
    redraw();
}

void canvas::set_delay(size_t delay)
{
    this->delay = delay;
}

void canvas::set_hor()
{
    vertical = false;
    horizontal = true;
}
void canvas::set_ver()
{
    horizontal = false;
    vertical = true;
}

void canvas::clear()
{
    for (polygon *f : shapes)
        delete f;
    shapes.clear();
    finished = true;

    redraw();
}

void canvas::get_time(double &time)
{
    time = 0;
    for (polygon *p : shapes)
        time += p->paint_time(image);
}
