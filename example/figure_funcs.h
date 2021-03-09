#ifndef FIGURE_FUNCS_H
#define FIGURE_FUNCS_H

#include <vector>
#include <stdio.h>
#include "data_types.h"

typedef std::vector<line> figure;

void shift(figure &edges, shift_params &param);

void rotate(figure &edges, rotate_params &param);

void scale(figure &edges, scale_params &param);

int get_edge(figure &edges, changing_edge &edge);

int import_fig(figure &edges, FILE *f);

void export_fig(figure &edges, FILE *f);

#endif // FIGURE_FUNCS_H
