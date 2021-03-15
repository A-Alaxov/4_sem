#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include <stdio.h>
#include "data_types.h"

enum operations{
    SHIFT,
    ROTATE,
    SCALE,
    GET_EDGE,
    IMPORT,
    EXPORT
};

union parametrs{
    shift_params shift;
    rotate_params rotate;
    scale_params scale;
    screen_edge edge;
    FILE *f;
};

int entry(parametrs &params, operations func);

#endif // MAIN_FUNC_H
