#include <math.h>
#include <time.h>
#include <QSize>
#include <QWidget>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include "polygon.h"

polygon::polygon(const QColor &fg, const QColor &paint_col)
    :fg(fg), paint_col(paint_col)
{
}

void polygon::draw(QPainter &painter) const
{
    painter.setPen(QPen(fg));

    for (edge edge: edges)
    {
        painter.drawLine(edge.p1->x, edge.p1->y, edge.p2->x, edge.p2->y);
    }

    for (point *point : points)
    {
        QString text("(");
        text.append(QString::number(point->x));
        text.append("; ");
        text.append(QString::number(point->y));
        text.append(")");
        painter.drawText(point->x - (text.indexOf(';') + 1) * 5, point->y - 5, text);
    }
}

void polygon::find_max(int &max) const
{
    max = points[0]->x;
    for (point *p : points)
        if (p->x > max)
            max = p->x;
}

void polygon::paint_sleep(size_t delay)
{
    QTime end = QTime::currentTime().addMSecs(delay);
    while (QTime::currentTime() < end)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    }
}

void polygon::draw_line(int x, int y, int max, QPainter &painter, QImage *image, QColor bg)
{
    while (x < max)
    {
        if (image->pixelColor(x, y) == paint_col)
            painter.setPen(bg);
        else
            painter.setPen(paint_col);

        painter.drawPoint(x, y);
        x++;
    }
}

void polygon::paint(QPainter &painter, QImage *image, size_t delay, QWidget *widget, QColor bg)
{
    int max;
    find_max(max);

    for (edge edge: edges)
    {
        point beg(edge.p1), end(edge.p2);

        if (beg.y == end.y)
            continue;

        if (beg.y > end.y)
        {
            int tmp = beg.y;
            beg.y = end.y;
            end.y = tmp;

            tmp = beg.x;
            beg.x = end.x;
            end.x = tmp;
        }

        float сtg = (float) (end.x - beg.x) / (end.y - beg.y);

        float x = beg.x;
        int y = beg.y;

        while (y != end.y)
        {
            draw_line(round(x), y, max, painter, image, bg);
            if (delay)
            {
                paint_sleep(delay);
                widget->update();
            }
            x += сtg;
            y += 1;
        }
    }
}

double polygon::paint_time(QImage *image)
{
    int max;
    find_max(max);

    QImage *img = new QImage(image->size(), QImage::Format_RGBA64);
    QPainter painter(img);

    clock_t clk = clock();
    paint(painter, img, 0, nullptr, QColor(0, 0, 0));
    clk = clock() - clk;

    return (double) clk / CLOCKS_PER_SEC;
}

void polygon::add_point(point *point, bool hor, bool ver)
{
    if (hor)
        point->y = points[points.size() - 1]->y;
    if (ver)
        point->x = points[points.size() - 1]->x;

    points.push_back(point);
    if (new_edge)
        edges.push_back(edge(points[points.size() - 1], points[points.size() - 2]));
    new_edge = true;
}

void polygon::add_hole()
{
    close();
    new_edge = false;
    start_pos = points.size();
}

void polygon::close()
{
    if (points.size() != edges.size())
        edges.push_back(edge(points[start_pos], points[points.size() - 1]));
}
