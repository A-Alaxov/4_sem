#include "dot.h"
#include "errors.h"
#include <cmath>

void shift_dot(dot &dot, shift_params &param) {
    dot.x += param.x_shift;
    dot.y += param.y_shift;
    dot.z += param.z_shift;
}

void get_opposite(dot &opp_centre, dot &centre) {
    opp_centre.x = -centre.x;
    opp_centre.y = -centre.y;
    opp_centre.z = -centre.z;
}

void change_coord_sys(dot &cur_dot, dot &centre) {
    cur_dot.x -= centre.x;
    cur_dot.y -= centre.y;
    cur_dot.z -= centre.z;
}

int rotate_in_flat(double &coord_1, double &coord_2, trig_funcs &angle) {
    double tmp_1 = coord_1;
    double tmp_2 = coord_2;

    coord_1 = tmp_1 * angle.cos - tmp_2 * angle.sin;
    coord_2 = tmp_1 * angle.sin + tmp_2 * angle.cos;

    return OK;
}

int rotate_dot(dot &dot, trig_angles &angles) {
    rotate_in_flat(dot.x, dot.y, angles.xy_flat);
    rotate_in_flat(dot.y, dot.z, angles.yz_flat);
    rotate_in_flat(dot.z, dot.x, angles.zx_flat);

    return OK;
}

void scale_dot(dot &dot, scale_coefs &coefs) {
    dot.x *= coefs.x_scale;
    dot.y *= coefs.y_scale;
    dot.z *= coefs.z_scale;
}

void get_screen_dot(dot &scr_dot, dot &orig_dot) {
    scr_dot.x = orig_dot.y - orig_dot.x * sqrt(3) / 2;
    scr_dot.y = orig_dot.x / 2 - orig_dot.z;
}
