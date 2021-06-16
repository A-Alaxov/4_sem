#include <math.h>
#include "cutter.hpp"

cutter::cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col)
    :state(START_FIG), cut_col(cut_col), vis_col(vis_col), seg_col(seg_col), fig(cut_col)
{
}

void cutter::next_state()
{
    if (state == START_FIG)
        state = PROC_FIG;
    else if (state == PROC_FIG)
        state = FIRST_LINE_POINT;
    else if (state == FIRST_LINE_POINT)
        state = SECOND_LINE_POINT;
    else if (state == SECOND_LINE_POINT)
        state = FIRST_LINE_POINT;
}

void cutter::end_cutter()
{
    if (state == PROC_FIG)
        next_state();
    fig.end_fig();
}

void cutter::add_point(long x, long y, bool is_hor, bool is_vert, bool is_paral)
{
    approx_point(x, y, is_hor, is_vert, is_paral);
    if (state == START_FIG)
    {
        fig = cut_fig(cut_col);
        fig.add_point(point(x, y));
    }
    else if (state == PROC_FIG)
    {
        if (render_check)
            fig.add_point(point(x, y));
        else
            fig.change_last(point(x, y));
        render_check = true;
    }
    else if (state == FIRST_LINE_POINT)
    {
        lines.push_back(line(seg_col, x, y));
    }
    else if (state == SECOND_LINE_POINT)
    {
        lines[lines.size() - 1].set_p2(point(x, y));
    }

    if (state != PROC_FIG)
        next_state();
}

void cutter::render_point(long x, long y, bool is_hor, bool is_vert, bool is_paral)
{
    approx_point(x, y, is_hor, is_vert, is_paral);
    if (state == PROC_FIG)
    {
        if (render_check)
        {
            fig.add_point(point(x, y));
            render_check = false;
        }
        else
            fig.change_last(point(x, y));
    }
    else if (state == SECOND_LINE_POINT)
    {
        lines[lines.size() - 1].set_p2(point(x, y));
    }
}

void cutter::approx_point(long &x, long &y, bool is_hor, bool is_vert, bool is_paral)
{
    if (state == START_FIG)
        return;

    if (state == PROC_FIG)
    {
        if (is_hor)
        {
            y = fig.get_last().y();
            return;
        }
        if (is_vert)
        {
            x = fig.get_last().x();
            return;
        }
        return;
    }

    if (state == SECOND_LINE_POINT)
    {
        if (is_hor)
        {
            y = lines[lines.size() - 1].get_p1().y();
            return;
        }
        if (is_vert)
        {
            x = lines[lines.size() - 1].get_p1().x();
            return;
        }
        if (is_paral)
        {
            double angle = atan((lines[lines.size() - 1].get_p1().y() - y) /
                                (lines[lines.size() - 1].get_p1().x() - x));
            double min_dif = 0, rib_angle = 0;
            long min_ind = 0;
            for (long i = 0; i < fig.edges_count(); i++)
            {
                rib_angle = atan((fig.get_edge(i).get_p1().y() - fig.get_edge(i).get_p2().y()) /
                                 (fig.get_edge(i).get_p1().x() - fig.get_edge(i).get_p2().x()));
                if (i == 0 || fabs(fabs(angle - rib_angle) - M_PI_2) > min_dif)
                {
                    min_dif = fabs(fabs(angle - rib_angle) - M_PI_2);
                    min_ind = i;
                }
            }
            rib_angle = atan((fig.get_edge(min_ind).get_p1().y() - fig.get_edge(min_ind).get_p2().y()) /
                             (fig.get_edge(min_ind).get_p1().x() - fig.get_edge(min_ind).get_p2().x()));
            min_dif = angle - rib_angle;
            double dist = sqrt(pow((lines[lines.size() - 1].get_p1().x() - x), 2) +
                               pow((lines[lines.size() - 1].get_p1().y() - y), 2));
            dist *= cos(min_dif);
            if (x < lines[lines.size() - 1].get_p1().x())
                dist *= -1;
            x = lines[lines.size() - 1].get_p1().x() + dist * cos(rib_angle);
            y = lines[lines.size() - 1].get_p1().y() + dist * sin(rib_angle);

            point n_in = point(fig.get_edge(min_ind).get_p2().y() - fig.get_edge(min_ind).get_p1().y(),
                             -(fig.get_edge(min_ind).get_p2().x() - fig.get_edge(min_ind).get_p1().x()));
            if (rib_angle)
                x -= (x - lines[lines.size() - 1].get_p1().x() + (y - lines[lines.size() - 1].get_p1().y()) * n_in.y() / n_in.x());

            return;
        }
    }

    long dist = 0;
    point min_dist;
    for (long i = 0; i < fig.edges_count(); i++)
    {
        point proj = fig.get_edge(i).find_distance(point(x, y));
        if (i == 0 || (pow(proj.x() - x, 2) + pow(proj.y() - y, 2)) < dist)
        {
            dist = pow(proj.x() - x, 2) + pow(proj.y() - y, 2);
            min_dist = proj;
        }
    }
    if (dist < 36)
    {
        x = min_dist.x();
        y = min_dist.y();
    }
}

void cutter::clear()
{
    fig = cut_fig(cut_col);
    state = START_FIG;
    render_check = true;
    lines.clear();
}

void cutter::draw(QPainter &painter)
{
    fig.paint(painter);
    for (auto _line : lines)
        _line.paint(painter);
    for (line _line : vis_lines)
        _line.paint(painter);
    vis_lines.clear();
}

void cutter::set_cut_col(const QColor &color)
{
    cut_col = color;
    fig.set_fg(color);
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

bool cutter::cut()
{
    line vis_line(vis_col);
    long conv = fig.is_convex();
    if (!conv)
        return false;
    for (line _line : lines)
    {
        bool is_vis = cut_line(vis_line, _line, conv);
        if (is_vis)
            vis_lines.push_back(vis_line);
    }
    return true;
}

long cutter::scalar_prod(point v1, point v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

bool cutter::cut_line(line &res, line &src, long conv)
{
    long m = fig.edges_count();
    point D = src.get_p2() - src.get_p1();
    double t_low = 0, t_high = 1;
    for (long i = 0; i < m; i++)
    {
        point f = fig.get_edge(i).get_p1(), p2 = fig.get_edge(i).get_p2();
        point n_in = point(conv * (p2.y() - f.y()), -conv * (p2.x() - f.x()));
        point W = src.get_p1() - f;
        double Wsc = scalar_prod(W, n_in);
        double Dsc = scalar_prod(D, n_in);

        if (Dsc)
        {
            double t = - Wsc / Dsc;
            if (Dsc > 0)
            {
                if (t > 1)
                    return false;
                else if (t > t_low)
                {
                    t_low = t;
                }
            }
            else
            {
                if (t < 0)
                    return false;
                else if (t < t_high)
                {
                    t_high = t;
                }
            }
        }
        else if (Wsc < 0)
            return false;
    }
    if (t_low > t_high)
        return false;
    res.set_p1(src.get_p1() + (src.get_p2() - src.get_p1()) * t_low);
    res.set_p2(src.get_p1() + (src.get_p2() - src.get_p1()) * t_high);
    return true;
}
