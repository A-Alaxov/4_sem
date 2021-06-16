#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include <QImage>
#include <QPainter>

struct point
{
    point()
        :x(0), y(0) {}
    point(int x, int y)
        :x(x), y(y) {}
    point(const point *p)
        :x(p->x), y(p->y) {}
    int x;
    int y;
};

struct edge
{
    edge(point *p1, point *p2)
        :p1(p1), p2(p2) {}
    point *p1;
    point *p2;
};

class figure
{
public:
    figure(const QColor &fg, const QColor &paint_col);
    ~figure() = default;

    void draw(QPainter &painter) const;
    void paint(QPainter &painter, QImage *image, size_t delay, QWidget *widget, point seed);
    void close();

    void add_point(point *point, bool hor, bool ver);
    void add_hole();

    double paint_time(QImage *image, point seed);

private:
    static void paint_sleep(size_t delay);

    bool new_edge = false;
    size_t start_pos = 0;

    QColor fg;
    QColor paint_col;

    std::vector<point *> points;
    std::vector<edge> edges;

};

#endif // FIGURE_H
