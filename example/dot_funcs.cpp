#include "dot_funcs.h"
#include "errors.h"
#include <cmath>

void shift_dot(dot &dot, shift_params &param) {
    dot.x += param.x_shift;
    dot.y += param.y_shift;
    dot.z += param.z_shift;
}

void rotate_dot(dot &dot, rotate_params &param) {
    double x = dot.x;
    double y = dot.y;
    double angle = (param.xy_angle * M_PI) / 180;

    dot.x = param.centre.x + (x - param.centre.x) * cos(angle)
            - (y - param.centre.y) * sin(angle);
    dot.y = param.centre.y + (x - param.centre.x) * sin(angle)
            + (y - param.centre.y) * cos(angle);

    y = dot.y;
    double z = dot.z;
    angle = (param.yz_angle * M_PI) / 180;

    dot.y = param.centre.y + (y - param.centre.y) * cos(angle)
            - (z - param.centre.z) * sin(angle);
    dot.z = param.centre.z + (y - param.centre.y) * sin(angle)
            + (z - param.centre.z) * cos(angle);

    z = dot.z;
    x = dot.x;
    angle = (param.zx_angle * M_PI) / 180;

    dot.z = param.centre.z + (z - param.centre.z) * cos(angle)
            - (x - param.centre.x) * sin(angle);
    dot.x = param.centre.x + (z - param.centre.z) * sin(angle)
            + (x - param.centre.x) * cos(angle);
}

void scale_dot(dot &dot, scale_params &param) {
    double dx = dot.x - param.centre.x;
    double dy = dot.y - param.centre.y;
    double dz = dot.z - param.centre.z;
    dot.x = param.centre.x + dx * param.x_scale;
    dot.y = param.centre.y + dy * param.y_scale;
    dot.z = param.centre.z + dz * param.z_scale;
}

void change_dot(dot &orig_dot, dot &changed_dot) {
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

void export_dot(dot &dot, FILE *f) {
    fprintf(f, "%lf %lf %lf\n", dot.x, dot.y, dot.z);
}
