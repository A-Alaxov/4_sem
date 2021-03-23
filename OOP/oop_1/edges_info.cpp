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

int check_edges(const edges_info &fig_edges, const int &count) {
    if (!fig_edges.edges)
        return INCORRECT_FIG;

    int rc = OK;

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

int edges_alloc(edges_info &fig_edges, const int &count) {
    line *tmp_edges = (line*)malloc(count * sizeof(line));
    if (!tmp_edges)
        return MEM_ERR;

    fig_edges.edges = tmp_edges;
    fig_edges.count = count;
    return OK;
}

int get_screen_edges(edges_info &scr_edges, const edges_info &fig_edges) {
    int rc = edges_alloc(scr_edges, fig_edges.count);

    for (int i = 0; (!rc) && (i < fig_edges.count); i++) {
        rc = edge_copy(scr_edges.edges[i], fig_edges.edges[i]);
    }

    return rc;
}

int scan_edges_count(int &count, FILE *const f) {
    if (fscanf(f, "%d", &count) != 1)
        return WRONG_DATA;

    return OK;
}

int import_edges(edges_info &fig_edges, FILE *const f) {
    int count;

    int rc = scan_edges_count(count, f);
    if (rc)
        return rc;

    rc = edges_alloc(fig_edges, count);
    if (rc)
        return rc;

    for (int i = 0; (!rc) && (i < fig_edges.count); i++) {
        rc = import_edge(fig_edges.edges[i], f);
    }

    if (rc)
        free_edges(fig_edges);

    return rc;
}

int export_edges(FILE *const f, const edges_info &fig_edges) {
    if (!fig_edges.edges)
        return NO_DATA;

    fprintf(f, "%d\n", fig_edges.count);

    for (int i = 0; i < fig_edges.count; i++) {
        export_edge(f, fig_edges.edges[i]);
    }

    return OK;
}
