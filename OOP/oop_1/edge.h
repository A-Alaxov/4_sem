#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>

struct line{
    int dot1;
    int dot2;
};

bool check_line(line &edge, int &count);

int import_edge(line &edge, FILE *f);

int export_edge(FILE *f, line &edge);

#endif // EDGE_H
