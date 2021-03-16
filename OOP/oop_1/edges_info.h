#ifndef EDGES_H
#define EDGES_H

#include "edge.h"
#include <stdio.h>

struct edges_info {
    line *edges;
    int count;
};

edges_info init_edges();

void free_edges(edges_info &fig_edges);

bool check_edges(const edges_info &fig_edges, const int &count);

int get_cur_line(line &cur_edge, const int &number, const edges_info &fig_edges);

int import_all_edges(edges_info &fig_edges, FILE *const f);

int export_all_edges(FILE *const f, const edges_info &fig_edges);

#endif // EDGES_H
