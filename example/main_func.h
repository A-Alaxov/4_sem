#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include <stdio.h>
#include "data_types.h"

typedef enum {
    SHIFT,
    ROTATE,
    SCALE,
    GET_EDGE,
    IMPORT,
    EXPORT
} operations;

typedef union {
    shift_params shift;
    rotate_params rotate;
    scale_params scale;
    changing_edge edge;
    FILE *f;
} parametrs;

int main_func(operations func, parametrs &params);

#endif // MAIN_FUNC_H
