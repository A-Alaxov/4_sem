#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>

struct line{
    int dot1;
    int dot2;
};

bool check_line(const line &edge, const int &count);

int import_edge(line &edge, FILE *const f);

int export_edge(FILE *const f, const line &edge);

#endif // EDGE_H
