#ifndef FIGURE_FUNCS_H
#define FIGURE_FUNCS_H

#include "data_types.h"
#include <stdio.h>

struct figure {
    dot *fig_dots;
    line *fig_edges;
    int dots_count;
    int edges_count;
};

int shift(figure &edges, shift_params &param);

int rotate(figure &edges, rotate_params &param);

int scale(figure &edges, scale_params &param);

int get_edge(screen_edge &edge, figure &scr_edge);

int import_fig(figure &edges, FILE *f);

int export_fig(FILE *f, figure &edges);

#endif // FIGURE_FUNCS_H
