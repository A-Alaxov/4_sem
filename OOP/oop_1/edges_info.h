#ifndef EDGES_H
#define EDGES_H

#include "data_types.h"
#include <stdio.h>

edges_info init_edges();

void free_edges(edges_info &fig_edges);

bool check_edges(edges_info &fig_edges, int &count);

int get_cur_line(line &cur_edge, int &number, edges_info &fig_edges);

int export_all_edges(FILE *f, edges_info &fig_edges);

#endif // EDGES_H
