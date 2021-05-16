#include <math.h>
#include <time.h>
#include <QSize>
#include <QWidget>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <stack>
#include "figure.h"

figure::figure(const QColor &fg, const QColor &paint_col)
    :fg(fg), paint_col(paint_col)
{
}

void figure::draw(QPainter &painter) const
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

void figure::paint_sleep(size_t delay)
{
    QTime end = QTime::currentTime().addMSecs(delay);
    while (QTime::currentTime() < end)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    }
}

void figure::paint(QPainter &painter, QImage *image, size_t delay, QWidget *widget, point seed)
{
    painter.setPen(paint_col);
    std::stack<point> stk;
    stk.push(seed);

    while (stk.size())
    {
        point pxl = stk.top();
        stk.pop();
        painter.drawPoint(pxl.x, pxl.y);

        int wx = pxl.x;

        pxl.x++;
        while (image->pixelColor(pxl.x, pxl.y) != fg)
        {
            painter.drawPoint(pxl.x, pxl.y);
            pxl.x++;
        }
        int xright = pxl.x - 1;

        pxl.x = wx;

        pxl.x--;
        while (image->pixelColor(pxl.x, pxl.y) != fg)
        {
            painter.drawPoint(pxl.x, pxl.y);
            pxl.x--;
        }
        int xleft = pxl.x + 1;

        pxl.x = wx;

        pxl.x = xleft;
        pxl.y++;
        while (pxl.x <= xright)
        {
            int f = 0;
            //while ((image->pixelColor(pxl.x, pxl.y) != fg) && (image->pixelColor(pxl.x, pxl.y) != paint_col) && (pxl.x <= xright))
            while ((image->pixelColor(pxl.x, pxl.y) != fg) && (image->pixelColor(pxl.x, pxl.y) != paint_col) && (pxl.x < xright))
            {
                //if (!f)
                //    f = 1;
                f = 1;
                pxl.x++;
            }

            if (f)
            {
                if ((pxl.x == xright) && (image->pixelColor(pxl.x, pxl.y) != fg) && (image->pixelColor(pxl.x, pxl.y) != paint_col))
                    stk.push(pxl);
                else
                {
                    point tmp(pxl.x - 1, pxl.y);
                    stk.push(tmp);
                }
                //f = 0;
            }
            f = 0;

            int xn = pxl.x;
            while (((image->pixelColor(pxl.x, pxl.y) == fg) || (image->pixelColor(pxl.x, pxl.y) == paint_col)) && (pxl.x < xright))
            {
                pxl.x++;
            }
            if (pxl.x == xn)
                pxl.x++;
        }

        pxl.y -= 2;
        pxl.x = xleft;
        while (pxl.x <= xright)
        {
            int f = 0;
            //while ((image->pixelColor(pxl.x, pxl.y) != fg) && (image->pixelColor(pxl.x, pxl.y) != paint_col) && (pxl.x <= xright))
            while ((image->pixelColor(pxl.x, pxl.y) != fg) && (image->pixelColor(pxl.x, pxl.y) != paint_col) && (pxl.x < xright))
            {
                //if (!f)
                //    f = 1;
                f = 1;
                pxl.x++;
            }

            if (f)
            {
                if ((pxl.x == xright) && (image->pixelColor(pxl.x, pxl.y) != fg) && (image->pixelColor(pxl.x, pxl.y) != paint_col))
                    stk.push(pxl);
                else
                {
                    point tmp(pxl.x - 1, pxl.y);
                    stk.push(tmp);
                }
                //f = 0;
            }
            f = 0;

            int xn = pxl.x;
            while (((image->pixelColor(pxl.x, pxl.y) == fg) || (image->pixelColor(pxl.x, pxl.y) == paint_col)) && (pxl.x < xright))
            {
                pxl.x++;
            }
            if (pxl.x == xn)
                pxl.x++;
        }
        if (delay)
        {
            paint_sleep(delay);
            widget->update();
        }
    }
}

double figure::paint_time(QImage *image, point seed)
{
    QImage *img = new QImage(image->size(), QImage::Format_RGBA64);
    QPainter painter(img);
    draw(painter);

    clock_t clk = clock();
    paint(painter, img, 0, nullptr, seed);
    clk = clock() - clk;

    return (double) clk / CLOCKS_PER_SEC;
}

void figure::add_point(point *point, bool hor, bool ver)
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

void figure::add_hole()
{
    close();
    new_edge = false;
    start_pos = points.size();
}

void figure::close()
{
    if (points.size() != edges.size())
        edges.push_back(edge(points[start_pos], points[points.size() - 1]));
}
