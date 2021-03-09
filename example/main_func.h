#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include <vector>

#define OK 0
#define WRONG_INDEX -1

typedef enum {
    SHOW,
    SHIFT,
    ROTATE,
    SCALE,
    GET_EDGE
} operations;

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
    line edge;
    size_t number;
} changing_edge;

typedef union {
    shift_params shift;
    rotate_params rotate;
    scale_params scale;
    changing_edge edge;
} parametrs;

typedef std::vector<line> figure;

int main_func(operations func, parametrs &params);

#endif // MAIN_FUNC_H
