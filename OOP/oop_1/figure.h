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

int shift(fig_info &figure, const shift_params &param);

int rotate(fig_info &figure, const rotate_params &param);

int scale(fig_info &figure, const scale_params &param);

int get_screen_edge(screen_edge &scr_edge, const fig_info &figure);

int import_fig(fig_info &figure, const char *file_name);

int export_fig(const char *file_name, const fig_info &figure);

#endif // FIGURE_FUNCS_H
