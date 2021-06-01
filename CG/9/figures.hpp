#ifndef FIGURES_HPP
#define FIGURES_HPP

#include <QColor>
#include <QPainter>

class Figure
{
public:
    Figure(const QColor &fg = QColor(0, 0, 0), const QColor &bg = QColor(255, 255, 255))
        :fg(fg), bg(bg)
    {
    }

    virtual void paint(QPainter &painter) const = 0;
    virtual ~Figure() {}

    void set_fg(const QColor &color) {fg = color;}
    void set_bg(const QColor &color) {bg = color;}

protected:
    QColor fg;
    QColor bg;
};

class point : public Figure
{
public:
    explicit point(const QColor &fg = QColor(0, 0, 0))
        :Figure(fg)
    {
    }

    point(double x, double y, const QColor &fg = QColor(0, 0, 0))
        :Figure(fg), _x(x), _y(y)
    {
    }
    virtual void paint(QPainter &painter) const override;

    double x() const;
    double y() const;
    void set_x(long x);
    void set_y(long y);

    point operator-(const point& p);
    point operator+(const point& p);
    point operator*(double num);
    point operator/(double num);
    bool operator<(double eps);

private:
    double _x = 0;
    double _y = 0;
};

class line : public Figure
{
public:
    explicit line(const QColor &fg)
        :Figure(fg), p1(fg), p2(fg)
    {
    }
    line(const QColor &fg, long x, long y)
        :Figure(fg), p1(point(x, y, fg)), p2(point(x, y, fg))
    {
    }
    line(point p1, point p2)
        :p1(p1), p2(p2)
    {
    }

    virtual void paint(QPainter &painter) const override;

    point find_distance(const point &a);
    point get_p1();
    point get_p2();
    void set_p1(const point &p);
    void set_p2(const point &p);

private:
    point p1;
    point p2;
};

class polygon : public Figure
{
public:
    explicit polygon(const QColor &fg)
        :Figure(fg)
    {
    }

    virtual void paint(QPainter &painter) const override;

    long edges_count() { return edges.size(); }
    point get_last() { return points[points.size() - 2]; }
    line get_edge(long index);
    std::vector<line> get_edges() { return edges; }
    long is_convex();

    void add_point(point point);
    void change_last(point point);
    void end_fig_with_pop();
    void end_fig();

private:
    long sign(long num);
    std::vector<point> points;
    std::vector<line> edges;
};

#endif // FIGURES_HPP
