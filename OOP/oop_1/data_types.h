#ifndef DATA_TYPES_H
#define DATA_TYPES_H

struct dot {
    double x;
    double y;
    double z;
};

struct dots_info {
    dot *dots;
    int count;
};

struct line{
    int dot1;
    int dot2;
};

struct edges_info {
    line *edges;
    int count;
};

struct shift_params {
    double x_shift;
    double y_shift;
    double z_shift;
};

struct rotate_params {
    dot centre;

    double xy_angle;
    double yz_angle;
    double zx_angle;
};

struct scale_coefs {
    double x_scale;
    double y_scale;
    double z_scale;
};

struct scale_params {
    dot centre;
    scale_coefs coefs;
};

struct screen_edge {
    dot dot1;
    dot dot2;

    int number;
};

#endif // DATA_TYPES_H
