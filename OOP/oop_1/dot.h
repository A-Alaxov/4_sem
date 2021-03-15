#ifndef DOT_FUNCS_H
#define DOT_FUNCS_H

#include "data_types.h"
#include <stdio.h>

struct trig_funcs {
    double sin;
    double cos;
};

struct trig_angles {
    trig_funcs xy_flat;
    trig_funcs yz_flat;
    trig_funcs zx_flat;
};

void shift_dot(dot &dot, shift_params &param);

void get_opposite(dot &opp_centre, dot &centre);

void change_coord_sys(dot &cur_dot, dot &centre);

int rotate_dot(dot &dot, trig_angles &angles);

void scale_dot(dot &dot, scale_coefs &coefs);

void get_screen_dot(dot &changed_dot, dot &orig_dot);

int import_dot(dot &dot, FILE *f);

int import_edge(line &edge, FILE *f);

void export_dot(FILE *f, dot &dot);

void export_edge(FILE *f, line &edge);

#endif // DOT_FUNCS_H
