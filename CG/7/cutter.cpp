#include <math.h>
#include "cutter.hpp"

cutter::cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col)
    :state(FIRST_RECT_POINT), cut_col(cut_col), vis_col(vis_col), seg_col(seg_col), rect(rectangle(cut_col))
{
}

void cutter::next_state()
{
    if (state == FIRST_RECT_POINT)
        state = SECOND_RECT_POINT;
    else if (state == SECOND_RECT_POINT)
        state = FIRST_LINE_POINT;
    else if (state == FIRST_LINE_POINT)
        state = SECOND_LINE_POINT;
    else if (state == SECOND_LINE_POINT)
        state = FIRST_LINE_POINT;
}

void cutter::add_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == FIRST_RECT_POINT)
    {
        rect = rectangle(cut_col, x, y);
    }
    else if (state == SECOND_RECT_POINT)
    {
        rect.set_p2(point(x, y));
    }
    else if (state == FIRST_LINE_POINT)
    {
        lines.push_back(line(seg_col, x, y));
    }
    else if (state == SECOND_LINE_POINT)
    {
        lines[lines.size() - 1].set_p2(point(x, y));
    }
    next_state();
}

void cutter::render_point(long x, long y, bool is_hor, bool is_vert)
{
    approx_point(x, y, is_hor, is_vert);
    if (state == SECOND_RECT_POINT)
    {
        rect.set_p2(point(x, y));
    }
    else if (state == SECOND_LINE_POINT)
    {
        lines[lines.size() - 1].set_p2(point(x, y));
    }
}

void cutter::approx_point(long &x, long &y, bool is_hor, bool is_vert)
{
    if (state == SECOND_LINE_POINT)
    {
        if (is_hor)
            y = lines[lines.size() - 1].get_p1().get_y();
        if (is_vert)
            x = lines[lines.size() - 1].get_p1().get_x();
    }

    long min_x = rect.get_left();
    long max_x = rect.get_right();
    long min_y = rect.get_bottom();
    long max_y = rect.get_top();

    long eps = 4;
    if (abs(rect.get_p1().get_x() - x) < eps && y >= min_y && y <= max_y)
        x = rect.get_p1().get_x();
    if (abs(rect.get_p2().get_x() - x) < eps && y >= min_y && y <= max_y)
        x = rect.get_p2().get_x();
    if (abs(rect.get_p1().get_y() - y) < eps && x >= min_x && x <= max_x)
        y = rect.get_p1().get_y();
    if (abs(rect.get_p2().get_y() - y) < eps && x >= min_x && x <= max_x)
        y = rect.get_p2().get_y();
}

void cutter::clear()
{
    rect = rectangle(cut_col);
    state = FIRST_RECT_POINT;
    lines.clear();
}

void cutter::draw(QPainter &painter)
{
    rect.paint(painter);
    for (auto _line : lines)
        _line.paint(painter);
    for (line _line : vis_lines)
        _line.paint(painter);
    vis_lines.clear();
}

void cutter::set_cut_col(const QColor &color)
{
    cut_col = color;
    rect.set_fg(color);
}

void cutter::set_vis_col(const QColor &color)
{
    vis_col = color;
}

void cutter::set_seg_col(const QColor &color)
{
    seg_col = color;
    for (line &_line : lines)
        _line.set_fg(color);
}

void cutter::cut()
{
    line vis_line(vis_col);
    for (line _line : lines)
    {
        bool is_vis = cut_line(vis_line, _line);
        if (is_vis)
            vis_lines.push_back(vis_line);
    }
}

bool cutter::log_mlt(const point_code &code1, const point_code &code2)
{
    bool mlt = 0;
    for (size_t i = 0; i < 4; i++)
        mlt += code1[i] && code2[i];

    return mlt;
}

int cutter::is_visible(line &src)
{
    long s1, s2;
    point_code t1, t2;
    find_point_code(s1, t1, src.get_p1());
    find_point_code(s2, t2, src.get_p2());

    int pr = 0;

    if ((!s1) && (!s2))
        pr = 1;
    else
    {
        bool p = log_mlt(t1, t2);
        if (p)
            pr = -1;
    }

    return pr;
}

void cutter::find_point_code(long &sum, point_code &t, const point &p)
{
    long min_x = rect.get_left();
    long max_x = rect.get_right();
    long min_y = rect.get_bottom();
    long max_y = rect.get_top();

    for (size_t i = 0; i < 4; i++)
        t[i] = false;

    if ((p.get_x()) < min_x)
        t[0] = true;
    else if ((p.get_x()) > max_x)
        t[1] = true;
    if ((p.get_y()) < min_y)
        t[2] = true;
    else if ((p.get_y()) > max_y)
        t[3] = true;

    sum = 0;
    for (size_t i = 0; i < 4; i++)
        sum += t[i];
}

bool cutter::cut_line(line &res, line &src)
{
    long rect_mas[4] ={ rect.get_left(), rect.get_right(), rect.get_bottom(), rect.get_top() };
    int Fl = 0;
    float m = 1;

    if (src.get_p2().get_x() - src.get_p1().get_x() == 0)
        Fl = -1;
    else
    {
        m = (src.get_p2().get_y() - src.get_p1().get_y()) / (src.get_p2().get_x() - src.get_p1().get_x());
        if (m == 0)
            Fl = 1;
    }

    for (int i = 0; i < 4; i++)
    {
        int pr = is_visible(src);
        if (pr == 1)
        {
            res.set_p1(src.get_p1());
            res.set_p2(src.get_p2());
            return pr;
        }
        else if (pr == -1)
            return pr;

        point_code T1, T2;
        long s1, s2;
        find_point_code(s1, T1, src.get_p1());
        find_point_code(s2, T2, src.get_p2());

        if (T1[i] == T2[i])
            continue;

        if (!T1[i])
        {
            point tmp = src.get_p1();
            src.set_p1(src.get_p2());
            src.set_p2(tmp);
        }

        if ((Fl != -1) && (i < 2))
        {
            src.set_p1(point(rect_mas[i], m * (rect_mas[i] - src.get_p1().get_x()) + src.get_p1().get_y()));
            continue;
        }
        if (Fl == 1)
            continue;

        if (Fl != -1)
            src.set_p1(point((rect_mas[i] - src.get_p1().get_y()) / m + src.get_p1().get_x(), src.get_p1().get_y()));

        src.set_p1(point(src.get_p1().get_x(), rect_mas[i]));

    }
    res.set_p1(src.get_p1());
    res.set_p2(src.get_p2());
    return true;
}
