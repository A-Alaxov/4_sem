#include "main_func.h"
#include "dot_funcs.h"

void show(figure &edges) {
    line lines;
    edges.clear();
    lines.dot1.x = 200;
    lines.dot1.y = 400;
    lines.dot1.z = -200;
    lines.dot2.x = 200;
    lines.dot2.y = 600;
    lines.dot2.z = -200;
    edges.push_back(lines);
    lines.dot1.y = 600;
    lines.dot2.x = 400;
    edges.push_back(lines);
    lines.dot1.x = 400;
    lines.dot2.y = 400;
    edges.push_back(lines);
    lines.dot1.y = 400;
    lines.dot2.x = 200;
    edges.push_back(lines);
    lines.dot1.x = 300;
    lines.dot1.y = 500;
    lines.dot1.z = 0;
    edges.push_back(lines);
    lines.dot2.y = 600;
    edges.push_back(lines);
    lines.dot2.x = 400;
    edges.push_back(lines);
    lines.dot2.y = 400;
    edges.push_back(lines);
}

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

    change_dot(edges[edge.number].dot1, edge.edge.dot1);
    change_dot(edges[edge.number].dot2, edge.edge.dot2);
    return OK;
}

int main_func(operations func, parametrs &params) {
    static figure edges;
    int rc = OK;

    if (func == SHOW) {
        show(edges);
    }
    if (func == SHIFT) {
        shift(edges, params.shift);
    }
    if (func == ROTATE) {
        rotate(edges, params.rotate);
    }
    if (func == SCALE) {
        scale(edges, params.scale);
    }
    if (func == GET_EDGE) {
        rc = get_edge(edges, params.edge);
    }

    return rc;
}
