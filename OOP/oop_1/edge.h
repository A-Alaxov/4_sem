#ifndef EDGE_H
#define EDGE_H

#include "data_types.h"
#include <stdio.h>

bool check_line(line &edge, int &count);

int export_edge(FILE *f, line &edge);

#endif // EDGE_H
