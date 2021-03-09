#ifndef DOT_FUNCS_H
#define DOT_FUNCS_H

#include "data_types.h"
#include <stdio.h>

void shift_dot(dot &dot, shift_params &param);

void rotate_dot(dot &dot, rotate_params &param);

void scale_dot(dot &dot, scale_params &param);

void change_dot(dot &orig_dot, dot &changed_dot);

int import_dot(dot &dot, FILE *f);

void export_dot(dot &dot, FILE *f);

#endif // DOT_FUNCS_H
