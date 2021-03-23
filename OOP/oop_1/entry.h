#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include "dot.h"
#include "dots_info.h"
#include "figure.h"

enum operations{
    SHIFT,
    ROTATE,
    SCALE,
    GET_FIG,
    IMPORT,
    EXPORT,
    FREE
};

union parametrs{
    shift_params shift;
    rotate_params rotate;
    scale_params scale;
    screen_fig screen_fig;
    char *file_name;
};

int entry(parametrs &params, const operations &func);

#endif // MAIN_FUNC_H
