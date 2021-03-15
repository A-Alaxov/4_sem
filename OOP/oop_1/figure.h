#ifndef FIGURE_FUNCS_H
#define FIGURE_FUNCS_H

#include "dots_info.h"
#include "edges_info.h"

struct fig_info {
    dots_info fig_dots;
    edges_info fig_edges;
    bool exist;
};

struct screen_edge {
    dot dot1;
    dot dot2;

    int number;
};

fig_info init_fig();

void free_fig(fig_info &figure);

int shift(fig_info &figure, shift_params &param);

int rotate(fig_info &figure, rotate_params &param);

int scale(fig_info &figure, scale_params &param);

int get_screen_edge(screen_edge &scr_edge, fig_info &figure);

int import_fig(fig_info &figure, char *f);

int export_fig(char *f, fig_info &figure);

#endif // FIGURE_FUNCS_H
