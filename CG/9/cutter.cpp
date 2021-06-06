#include <math.h>
#include "cutter.hpp"

cutter::cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col)
    :state(START_CUT), cut_col(cut_col), vis_col(vis_col), seg_col(seg_col), cut_fig(cut_col), enter_fig(seg_col), vis_fig(vis_col)
{
}

void cutter::next_state()
{
    if (state == START_CUT)
        state = PROC_CUT;
    else if (state == PROC_CUT)
        state = START_ENTER;
    else if (state == START_ENTER)
        state = PROC_ENTER;
    else if (state == PROC_ENTER)
        state = START_ENTER;
}

void cutter::end_cutter()
{
    if (state == PROC_CUT)
        next_state();
    cut_fig.end_fig_with_pop();
}

void cutter::end_enter()
{
    if (state == PROC_ENTER)
        next_state();
    enter_fig.end_fig_with_pop();
}

void cutter::add_point(long x, long y, bool is_hor, bool is_vert, bool is_paral)
{
    approx_point(x, y, is_hor, is_vert, is_paral);
    if (state == START_CUT)
    {
        cut_fig = polygon(cut_col);
        cut_fig.add_point(point(x, y));
    }
    else if (state == PROC_CUT)
    {
        if (render_check)
            cut_fig.add_point(point(x, y));
        else
            cut_fig.change_last(point(x, y));
        render_check = true;
    }
    else if (state == START_ENTER)
    {
        enter_fig = polygon(seg_col);
        enter_fig.add_point(point(x, y));
        vis_fig = polygon(cut_col);
        render_check = true;
    }
    else if (state == PROC_ENTER)
    {
        if (render_check)
            enter_fig.add_point(point(x, y));
        else
            enter_fig.change_last(point(x, y));
        render_check = true;
    }

    if (state != PROC_CUT && state != PROC_ENTER)
        next_state();
}

void cutter::render_point(long x, long y, bool is_hor, bool is_vert, bool is_paral)
{
    approx_point(x, y, is_hor, is_vert, is_paral);
    if (state == PROC_CUT)
    {
        if (render_check)
        {
            cut_fig.add_point(point(x, y));
            render_check = false;
        }
        else
            cut_fig.change_last(point(x, y));
    }
    else if (state == PROC_ENTER)
    {
        if (render_check)
        {
            enter_fig.add_point(point(x, y));
            render_check = false;
        }
        else
            enter_fig.change_last(point(x, y));
    }
}

void cutter::approx_point(long &x, long &y, bool is_hor, bool is_vert, bool is_paral)
{
    if (state == START_CUT)
        return;

    if (state == PROC_CUT)
    {
        if (is_hor)
        {
            y = cut_fig.get_last().y();
            return;
        }
        if (is_vert)
        {
            x = cut_fig.get_last().x();
            return;
        }
        return;
    }

    if (state == PROC_ENTER)
    {
        if (is_hor)
        {
            y = enter_fig.get_last().y();
            return;
        }
        if (is_vert)
        {
            x = enter_fig.get_last().x();
            return;
        }
        if (is_paral)
        {
            double angle = atan((enter_fig.get_last().y() - y) /
                                (enter_fig.get_last().x() - x));
            double min_dif = 0, rib_angle = 0;
            long min_ind = 0;
            for (long i = 0; i < cut_fig.edges_count(); i++)
            {
                rib_angle = atan((cut_fig.get_edge(i).get_p1().y() - cut_fig.get_edge(i).get_p2().y()) /
                                 (cut_fig.get_edge(i).get_p1().x() - cut_fig.get_edge(i).get_p2().x()));
                if (i == 0 || fabs(fabs(angle - rib_angle) - M_PI_2) > min_dif)
                {
                    min_dif = fabs(fabs(angle - rib_angle) - M_PI_2);
                    min_ind = i;
                }
            }
            rib_angle = atan((cut_fig.get_edge(min_ind).get_p1().y() - cut_fig.get_edge(min_ind).get_p2().y()) /
                             (cut_fig.get_edge(min_ind).get_p1().x() - cut_fig.get_edge(min_ind).get_p2().x()));
            min_dif = angle - rib_angle;
            double dist = sqrt(pow((enter_fig.get_last().x() - x), 2) +
                               pow((enter_fig.get_last().y() - y), 2));
            dist *= cos(min_dif);
            if (x < enter_fig.get_last().x())
                dist *= -1;
            x = enter_fig.get_last().x() + dist * cos(rib_angle);
            y = enter_fig.get_last().y() + dist * sin(rib_angle);

            point n_in = point(cut_fig.get_edge(min_ind).get_p2().y() - cut_fig.get_edge(min_ind).get_p1().y(),
                             -(cut_fig.get_edge(min_ind).get_p2().x() - cut_fig.get_edge(min_ind).get_p1().x()));
            if (rib_angle)
                x -= (x - enter_fig.get_last().x() + (y - enter_fig.get_last().y()) * n_in.y() / n_in.x());

            return;
        }
    }

    long dist = 0;
    point min_dist;
    for (long i = 0; i < cut_fig.edges_count(); i++)
    {
        point proj = cut_fig.get_edge(i).find_distance(point(x, y));
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
    cut_fig = polygon(cut_col);
    state = START_CUT;
    render_check = true;
    enter_fig = polygon(cut_col);
    vis_fig = polygon(cut_col);
}

void cutter::draw(QPainter &painter)
{
    cut_fig.paint(painter);
    enter_fig.paint(painter);
    vis_fig.paint(painter);
}

void cutter::set_cut_col(const QColor &color)
{
    cut_col = color;
    cut_fig.set_fg(color);
}

void cutter::set_vis_col(const QColor &color)
{
    vis_col = color;
}

void cutter::set_seg_col(const QColor &color)
{
    seg_col = color;
    enter_fig.set_fg(color);
}

bool cutter::cut()
{
    long normal = cut_fig.is_convex();
    if (!normal)
        return false;

    vis_fig = enter_fig;
    for (auto cut_line : cut_fig.get_edges())
    {
        polygon new_vis_fig(vis_col);
        for (auto vis_line : vis_fig.get_edges())
        {
            point inter;
            bool is_inter = cut_line.find_intersection(inter, vis_line, normal);

            if (is_inter)
            {
                new_vis_fig.add_point(inter);
            }

            bool is_vis = cut_line.is_visible(vis_line.get_p2(), normal);
            if (is_vis)
                new_vis_fig.add_point(vis_line.get_p2());
        }

        new_vis_fig.end_fig();
        vis_fig = new_vis_fig;
    }
    return true;
}

long cutter::scalar_prod(point v1, point v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}
