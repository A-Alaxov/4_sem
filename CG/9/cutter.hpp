#ifndef CUTTER_HPP
#define CUTTER_HPP

#include <QPainter>
#include <vector>

#include "figures.hpp"

class cutter
{
    enum cutter_state
    {
        START_CUT,
        PROC_CUT,
        START_ENTER,
        PROC_ENTER,
    };

public:
    cutter(const QColor &cut_col, const QColor vis_col, const QColor seg_col);
    long get_state() { return state; }
    void clear();
    void draw(QPainter &painter);
    bool cut();
    void add_point(long x, long y, bool is_hor, bool is_vert, bool is_paral);
    void render_point(long x, long y, bool is_hor, bool is_vert, bool is_paral);
    void set_cut_col(const QColor &color);
    void set_vis_col(const QColor &color);
    void set_seg_col(const QColor &color);
    void end_cutter();
    void end_enter();

private:
    bool find_intersection(point &p, line &cut_line, line &pol_line, long norm);
    bool is_visible(const point &p, line &_line, long norm);
    void next_state();
    void approx_point(long &x, long &y, bool is_hor, bool is_vert, bool is_paral);
    long scalar_prod(point v1, point v2);

    cutter_state state;
    bool render_check = true;

    QColor cut_col;
    QColor vis_col;
    QColor seg_col;

    polygon cut_fig;
    polygon enter_fig;
    polygon vis_fig;
};

#endif // CUTTER_HPP
