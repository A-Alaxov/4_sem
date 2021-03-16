#ifndef DOTS_INFO_H
#define DOTS_INFO_H

#include "dot.h"
#include <stdio.h>

struct dots_info {
    dot *dots;
    int count;
};

struct rotate_params {
    dot centre;

    double xy_angle;
    double yz_angle;
    double zx_angle;
};

struct scale_params {
    dot centre;
    scale_coefs coefs;
};

dots_info init_dots();

void free_dots(dots_info &fig_dots);

int shift_all_dots(dots_info &fig_dots, const shift_params &param);

int rotate_all_dots(dots_info &fig_dots, const rotate_params &param);

int scale_all_dots(dots_info &fig_dots, const scale_params &param);

int get_edge_dots(dot &scr_dot, const int &number, const dots_info &fig_dots);

int import_all_dots(dots_info &fig_dots, FILE *const f);

int export_all_dots(FILE *const f, const dots_info &fig_dots);

#endif // DOTS_INFO_H
