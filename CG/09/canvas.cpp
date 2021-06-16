#include <iostream>
#include <QPointF>
#include <QApplication>
#include <QPen>
#include <QBrush>
#include "canvas.hpp"

canvas::canvas(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

canvas::~canvas()
{
}

long canvas::cut()
{
    if (_cutter.get_state() != 2)
        return 2;
    bool conv = _cutter.cut();
    this->update();
    return conv;
}

void canvas::end_cutter()
{
    if (_cutter.get_state() != 1)
        return;
    _cutter.end_cutter();
    process = not process;
    this->update();
}

void canvas::end_enter()
{
    if (_cutter.get_state() != 3)
        return;
    _cutter.end_enter();
    process = not process;
    this->update();
}

void canvas::set_bg(const QColor &color)
{
    bg = color;
}

void canvas::set_cut_col(const QColor &color)
{
    _cutter.set_cut_col(color);
    this->update();
}

void canvas::set_seg_col(const QColor &color)
{
    _cutter.set_seg_col(color);
    this->update();
}

void canvas::set_vis_col(const QColor &color)
{
    _cutter.set_vis_col(color);
    this->update();
}

void canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setBrush(bg);
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(0, 0, this->width(), this->height());

    _cutter.draw(painter);
}

void canvas::mousePressEvent(QMouseEvent *event)
{
    if (_cutter.get_state() != 1 && _cutter.get_state() != 3)
        process = not process;
    Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
    bool is_hor = false, is_vert = false, is_paral = false;
    if (key == Qt::ShiftModifier)
        is_hor = true;
    if (key == Qt::ControlModifier)
        is_vert = true;
    if (key == Qt::AltModifier)
        is_paral = true;
    _cutter.add_point(event->pos().x(), event->pos().y(), is_hor, is_vert, is_paral);
    this->update();
}

void canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!process)
        return;

    Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
    bool is_hor = false, is_vert = false, is_paral = false;
    if (key == Qt::ShiftModifier)
        is_hor = true;
    if (key == Qt::ControlModifier)
        is_vert = true;
    if (key == Qt::AltModifier)
        is_paral = true;
    _cutter.render_point(event->pos().x(), event->pos().y(), is_hor, is_vert, is_paral);
    this->update();
}

void canvas::clear()
{
    _cutter.clear();
    process = false;
    this->update();
}
