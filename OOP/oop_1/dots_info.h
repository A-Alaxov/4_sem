#ifndef DOTS_INFO_H
#define DOTS_INFO_H

#include "data_types.h"
#include <stdio.h>

dots_info init_dots();

void free_dots(dots_info &fig_dots);

int shift_all_dots(dots_info &fig_dots, shift_params &param);

int rotate_all_dots(dots_info &fig_dots, rotate_params &param);

int scale_all_dots(dots_info &fig_dots, scale_params &param);

int get_edge_dots(screen_edge &scr_edge, line &cur_edge, dots_info &fig_dots);

int import_all_dots(dots_info &fig_dots, FILE *f);

int export_all_dots(FILE *f, dots_info &fig_dots);

#endif // DOTS_INFO_H
