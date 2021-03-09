#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef struct {
    double x;
    double y;
    double z;
} dot;

typedef struct {
    dot dot1;
    dot dot2;
} line;

typedef struct {
    double x_shift;
    double y_shift;
    double z_shift;
} shift_params;

typedef struct {
    dot centre;

    double xy_angle;
    double yz_angle;
    double zx_angle;
} rotate_params;

typedef struct {
    dot centre;

    double x_scale;
    double y_scale;
    double z_scale;
} scale_params;

typedef struct {
    line line;
    int number;
} changing_edge;

#endif // DATA_TYPES_H
