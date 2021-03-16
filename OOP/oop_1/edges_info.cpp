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
    fig_edges.edges = NULL;
    fig_edges.count = 0;
}

bool check_edges(const edges_info &fig_edges, const int &count) {
    if (!fig_edges.edges)
        return false;

    bool rc = true;

    for (int i = 0; !rc && i < fig_edges.count; i++)
        rc = check_line(fig_edges.edges[i], count);

    return rc;
}

int get_cur_line(line &cur_edge, const int &number, const edges_info &fig_edges) {
    if (!fig_edges.edges)
        return NO_DATA;

    if (number >= fig_edges.count)
        return WRONG_INDEX;

    cur_edge = fig_edges.edges[number];

    return OK;
}

int import_all_edges(edges_info &fig_edges, FILE *const f) {
    int rc = OK;
    int i = 0;

    if (fscanf(f, "%d", &(fig_edges.count)) != 1)
        return WRONG_DATA;

    fig_edges.edges = (line*)malloc(fig_edges.count * sizeof(line));
    if (!fig_edges.edges)
        return MEM_ERR;

    while ((!rc) && (i < fig_edges.count)) {
        rc = import_edge(fig_edges.edges[i], f);

        i++;
    }

    if (rc)
        free_edges(fig_edges);

    return rc;
}

int export_all_edges(FILE *const f, const edges_info &fig_edges) {
    if (!fig_edges.edges)
        return NO_DATA;

    fprintf(f, "%d\n", fig_edges.count);

    for (int i = 0; i < fig_edges.count; i++) {
        export_edge(f, fig_edges.edges[i]);
    }

    return OK;
}
