#include "dot_funcs.h"
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

void rotate_dot(dot &dot, trig_angles &angles) {
    double x = dot.x;
    double y = dot.y;

    dot.x = x * angles.xy_cos - y * angles.xy_sin;
    dot.y = x * angles.xy_sin + y * angles.xy_cos;

    y = dot.y;
    double z = dot.z;

    dot.y = y * angles.yz_cos - z * angles.yz_sin;
    dot.z = y * angles.yz_sin + z * angles.yz_cos;

    z = dot.z;
    x = dot.x;

    dot.z = z * angles.zx_cos - x * angles.zx_sin;
    dot.x = z * angles.zx_sin + x * angles.zx_cos;
}

void scale_dot(dot &dot, scale_coefs &coefs) {
    dot.x *= coefs.x_scale;
    dot.y *= coefs.y_scale;
    dot.z *= coefs.z_scale;
}

void change_dot(dot &changed_dot, dot &orig_dot) {
    changed_dot.x = orig_dot.y - orig_dot.x * sqrt(3) / 2;
    changed_dot.y = orig_dot.x / 2 - orig_dot.z;
}

int import_dot(dot &dot, FILE *f) {
    if (fscanf(f, "%lf", &dot.x) != 1)
        return WRONG_DATA;
    if (fscanf(f, "%lf", &dot.y) != 1)
        return WRONG_DATA;
    if (fscanf(f, "%lf", &dot.z) != 1)
        return WRONG_DATA;
    return OK;
}

int import_edge(line &edge, FILE *f) {
    if (fscanf(f, "%d", &edge.dot1) != 1)
        return WRONG_DATA;
    if (fscanf(f, "%d", &edge.dot2) != 1)
        return WRONG_DATA;
    return OK;
}

void export_dot(FILE *f, dot &dot) {
    fprintf(f, "%lf %lf %lf\n", dot.x, dot.y, dot.z);
}

void export_edge(FILE *f, line &edge) {
    fprintf(f, "%d %d\n", edge.dot1, edge.dot2);
}
