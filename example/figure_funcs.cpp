#include "dot_funcs.h"
#include "figure_funcs.h"
#include "errors.h"

void shift(figure &edges, shift_params &params) {
    for (size_t i = 0; i < edges.size(); i++) {
        shift_dot(edges[i].dot1, params);
        shift_dot(edges[i].dot2, params);
    }
}

void rotate(figure &edges, rotate_params &params) {
    for (size_t i = 0; i < edges.size(); i++) {
        rotate_dot(edges[i].dot1, params);
        rotate_dot(edges[i].dot2, params);
    }
}

void scale(figure &edges, scale_params &params) {
    for (size_t i = 0; i < edges.size(); i++) {
        scale_dot(edges[i].dot1, params);
        scale_dot(edges[i].dot2, params);
    }
}

int get_edge(figure &edges, changing_edge &edge) {
    if (edge.number >= edges.size())
        return WRONG_INDEX;

    change_dot(edges[edge.number].dot1, edge.line.dot1);
    change_dot(edges[edge.number].dot2, edge.line.dot2);
    return OK;
}

int import_fig(figure &edges, FILE *f) {
    int rc = OK;
    line line;

    edges.clear();

    while (!rc) {
        rc = import_dot(line.dot1, f);

        if (!rc) {
            rc = import_dot(line.dot2, f);

            if (!rc) {
                edges.push_back(line);
            }
        }
    }

    if (feof(f))
        rc = OK;
    if (!edges.size())
        rc = EMPTY_FILE;

    return rc;
}

void export_fig(figure &edges, FILE *f) {
    for (size_t i = 0; i < edges.size(); i++) {
        export_dot(edges[i].dot1, f);
        export_dot(edges[i].dot2, f);
    }
}
