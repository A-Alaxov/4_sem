#ifndef DOT_FUNCS_H
#define DOT_FUNCS_H

#include <stdio.h>

struct dot {
    double x;
    double y;
    double z;
};

struct shift_params {
    double x_shift;
    double y_shift;
    double z_shift;
};

struct trig_funcs {
    double sin;
    double cos;
};

struct trig_angles {
    trig_funcs xy_flat;
    trig_funcs yz_flat;
    trig_funcs zx_flat;
};

struct scale_coefs {
    double x_scale;
    double y_scale;
    double z_scale;
};

int shift_dot(dot &dot, const shift_params &param);

int get_opposite(dot &opp_centre, const dot &centre);

int change_coord_sys(dot &cur_dot, const dot &centre);

int rotate_dot(dot &dot, const trig_angles &angles);

int scale_dot(dot &dot, const scale_coefs &coefs);

int get_screen_dot(dot &changed_dot, const dot &orig_dot);

int import_dot(dot &dot, FILE *const f);

int export_dot(FILE *const f, const dot &dot);

#endif // DOT_FUNCS_H
