#ifndef DOT_FUNCS_H
#define DOT_FUNCS_H

#include "main_func.h"

void shift_dot(dot &dot, shift_params &param);

void rotate_dot(dot &dot, rotate_params &param);

void scale_dot(dot &dot, scale_params &param);

void change_dot(dot &orig_dot, dot &changed_dot);

#endif // DOT_FUNCS_H
