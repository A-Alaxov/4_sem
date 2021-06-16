#include <QPen>
#include <math.h>

#include "figures.hpp"

void point::paint(QPainter &painter) const
{
    painter.setPen(QPen(fg));
    painter.drawPoint(_x, _y);
}

void line::paint(QPainter &painter) const
{
    painter.setPen(QPen(fg));
    painter.drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}

void polygon::paint(QPainter &painter) const
{
    painter.setPen(QPen(fg));
    for (auto edge : edges)
        painter.drawLine(edge.get_p1().x(), edge.get_p1().y(), edge.get_p2().x(), edge.get_p2().y());
}

point point::operator -(const point &p)
{
    return point(_x - p._x, _y - p._y);
}

point point::operator +(const point &p)
{
    return point(_x + p._x, _y + p._y);
}

point point::operator *(double num)
{
    return point(_x * num, _y * num);
}

point point::operator /(double num)
{
    return point(_x / num, _y / num);
}

bool point::operator <(double eps)
{
    if (fabs(_x) < eps && fabs(_y) < eps)
        return true;

    return false;
}

double point::x() const
{
    return _x;
}

double point::y() const
{
    return _y;
}

void point::set_x(long x)
{
    this->_x = x;
}

void point::set_y(long y)
{
    this->_y = y;
}

bool line::find_intersection(point &p, line &line, long norm)
{
    bool vis1 = is_visible(line.get_p1(), norm);
    bool vis2 = is_visible(line.get_p2(), norm);
    bool is_inter = (vis1 || vis2) && (!(vis1 && vis2));

    if (is_inter)
    {
        point cut_vec = get_p2() - get_p1();
        point pol_vec = line.get_p2() - line.get_p1();

        long nominator = cut_vec.y() * (line.get_p1().x() - get_p1().x()) -\
                         cut_vec.x() * (line.get_p1().y() - get_p1().y());
        long denominator = pol_vec.y() * cut_vec.x() - pol_vec.x() * cut_vec.y();

        if (denominator == 0)
        {
            p = line.get_p2();
        }
        else
        {
            double t = (double) nominator/ denominator;
            p = line.get_p1() + (line.get_p2() - line.get_p1()) * t;
        }
    }

    return is_inter;
}

bool line::is_visible(const point &p, long norm)
{
    point v1 = get_p2() - get_p1();
    point v2 = line(get_p2(), p).get_p2() - line(get_p2(), p).get_p1();

    long pr = v1.x() * v2.y() - v1.y() * v2.x();

    if (pr * norm >= 0)
        return true;

    return false;
}

point line::find_distance(const point &a)
{
    point p = p1 - p2;
    point h(0, 0);

    if (p.x() == 0)
    {
        h.set_x(p1.x());
        h.set_y(a.y());
    }
    else if (p.y() == 0)
    {
        h.set_x(a.x());
        h.set_y(p1.y());
    }
    else
    {
        double hy = ((p.x() * p.y() * (a.x() - p1.x()) + p1.y() * p.x() * p.x() +
                      p.y() * p.y() * a.y()) / (p.x() * p.x() + p.y() * p.y()));
        h.set_x((hy - p1.y()) / p.y() * p.x() + p1.x());
        h.set_y(hy);
    }

    return h;
}

point line::get_p1()
{
    return p1;
}

point line::get_p2()
{
    return p2;
}

void line::set_p1(const point &p)
{
    p1 = p;
}

void line::set_p2(const point &p)
{
    p2 = p;
}

line polygon::get_edge(long index)
{
    return edges[index];
}

long polygon::sign(long num)
{
    if (!num)
        return 0;
    return (num > 0) ? 1 : -1;
}

long polygon::is_convex()
{
    point p1, p2, p3;
    long x1, y1, x2, y2, r, prev = 0, curr;
    for (size_t i = 0; i < points.size() - 2; i++)
    {
        p1 = points[i];
        p2 = points[i + 1];
        p3 = points[i + 2];

        x1 = p2.x() - p1.x();
        y1 = p2.y() - p1.y();

        x2 = p3.x() - p2.x();
        y2 = p3.y() - p2.y();

        r = x1 * y2 - x2 * y1;
        curr = sign(r);

        if (!prev)
            prev = curr;
        if (curr && curr != prev)
            return 0;
    }

    p1 = points[points.size() - 2];
    p2 = points[points.size() - 1];
    p3 = points[0];

    x1 = p2.x() - p1.x();
    y1 = p2.y() - p1.y();

    x2 = p3.x() - p2.x();
    y2 = p3.y() - p2.y();

    r = x1 * y2 - x2 * y1;
    curr = sign(r);
    if (curr && curr != prev)
        return 0;

    p1 = points[points.size() - 1];
    p2 = points[0];
    p3 = points[1];

    x1 = p2.x() - p1.x();
    y1 = p2.y() - p1.y();

    x2 = p3.x() - p2.x();
    y2 = p3.y() - p2.y();

    r = x1 * y2 - x2 * y1;
    curr = sign(r);
    if (curr && curr != prev)
        return 0;

    point tmp;
    for (long i = 0; i < edges_count() - 1; i++)
        for (long j = i + 1; j < edges_count(); j++)
            if (edges[i].find_intersection(tmp, edges[j], prev))
                return 0;

    return prev;
}

void polygon::add_point(point point)
{
    points.push_back(point);
    if (points.size() > 1)
        edges.push_back(line(points[points.size() - 2], points[points.size() - 1]));
}

void polygon::change_last(point point)
{
    points[points.size() - 1] = point;
    if (points.size() > 1)
        edges[edges.size() - 1].set_p2(point);
}

void polygon::end_fig_with_pop()
{
    points.pop_back();
    if (points.size() > 1)
        edges[edges.size() - 1].set_p2(points[0]);
}

void polygon::end_fig()
{
    if (points.size() > 1)
        edges.push_back(line(points[points.size() - 1], points[0]));
}
