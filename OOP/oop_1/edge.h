#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>

struct line{
    int dot1;
    int dot2;
};

int check_line(const line &edge, const int &count);

int edge_copy(line &scr_edge, const line &fig_edge);

int import_edge(line &edge, FILE *const f);

int export_edge(FILE *const f, const line &edge);

#endif // EDGE_H
