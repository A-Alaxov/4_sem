#ifndef DOT_FUNCS_H
#define DOT_FUNCS_H

#include "data_types.h"
#include <stdio.h>

struct trig_angles {
    double xy_sin;
    double xy_cos;
    double yz_sin;
    double yz_cos;
    double zx_sin;
    double zx_cos;
};

void shift_dot(dot &dot, shift_params &param);

void get_opposite(dot &opp_centre, dot &centre);

void change_coord_sys(dot &cur_dot, dot &centre);

void rotate_dot(dot &dot, trig_angles &angles);

void scale_dot(dot &dot, scale_coefs &coefs);

void change_dot(dot &changed_dot, dot &orig_dot);

int import_dot(dot &dot, FILE *f);

int import_edge(line &edge, FILE *f);

void export_dot(FILE *f, dot &dot);

void export_edge(FILE *f, line &edge);

#endif // DOT_FUNCS_H
