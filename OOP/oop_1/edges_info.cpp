#include "edge.h"
#include "edges_info.h"
#include "errors.h"
#include <cstdlib>

edges_info init_edges() {
    edges_info fig_edges;
    fig_edges.edges = NULL;
    fig_edges.count = 0;

    return fig_edges;
}

void free_edges(edges_info &fig_edges) {
    free(fig_edges.edges);
    fig_edges.count = 0;
}

bool check_edges(edges_info &fig_edges, int &count) {
    if (!fig_edges.edges)
        return false;

    bool rc = true;

    for (int i = 0; !rc && i < fig_edges.count; i++)
        rc = check_line(fig_edges.edges[i], count);

    return rc;
}

int get_cur_line(line &cur_edge, int &number, edges_info &fig_edges) {
    if (!fig_edges.edges)
        return NO_DATA;

    if (number >= fig_edges.count)
        return WRONG_INDEX;

    cur_edge = fig_edges.edges[number];

    return OK;
}

int export_all_edges(FILE *f, edges_info &fig_edges) {
    if (!fig_edges.edges)
        return NO_DATA;

    fprintf(f, "%d\n", fig_edges.count);

    for (int i = 0; i < fig_edges.count; i++) {
        export_edge(f, fig_edges.edges[i]);
    }

    return OK;
}
