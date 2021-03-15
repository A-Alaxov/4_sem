#include "dots_info.h"
#include "edges_info.h"
#include "figure.h"
#include "errors.h"
#include <cstdlib>
#include <cmath>

fig_info init_fig() {
    fig_info figure;
    figure.fig_dots = init_dots();
    figure.fig_edges = init_edges();
    figure.exist = false;

    return figure;
}

void free_fig(fig_info &figure) {
    free_dots(figure.fig_dots);
    free_edges(figure.fig_edges);
    figure.exist = false;
}

bool check_fig(fig_info &figure) {
    if ((figure.exist) && (check_edges(figure.fig_edges, figure.fig_dots.count)))
        return true;
    else
        return false;
}

int shift(fig_info &figure, shift_params &params) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    int rc = shift_all_dots(figure.fig_dots, params);

    return rc;
}

int rotate(fig_info &figure, rotate_params &params) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    int rc = rotate_all_dots(figure.fig_dots, params);

    return rc;
}

int scale(fig_info &figure, scale_params &params) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    int rc = scale_all_dots(figure.fig_dots, params);

    return rc;
}

int get_screen_edge(screen_edge &scr_edge, fig_info &figure) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    line cur_line;

    int rc = get_cur_line(cur_line, scr_edge.number, figure.fig_edges);

    if (!rc)
        rc = get_edge_dots(scr_edge, cur_line, figure.fig_dots);

    return rc;
}

int import_fig(fig_info &figure, FILE *f) {
    int rc = OK;
    int len, i = 0;

    fig_info tmp_figure = init_fig();

    rc = import_all_dots(tmp_figure.fig_dots, f);

    if (!rc) {
        rc = import_all_edges(tmp_figure.fig_edges, f);

        if (rc)
            free_dots(tmp_figure.fig_dots);
    }

    if (!rc) {
        tmp_figure.exist = true;

        if (check_fig(tmp_figure)) {
            free_fig(figure);
            figure = tmp_figure;
        }
        else {
            free_fig(tmp_figure);
            rc = INCORRECT_FIG;
        }
    }

    if (fscanf(f, "%d", &(tmp_edges.dots_count)) != 1)
        return WRONG_DATA;

    tmp_edges.fig_dots = (dot*)malloc(tmp_edges.dots_count * sizeof(dot));
    if (!tmp_edges.fig_dots)
        return MEM_ERR;

    while ((!rc) && (i < tmp_edges.dots_count)) {
        rc = import_dot(edges.fig_dots[i], f);

        i++;
    }

    if (!rc) {
        if (fscanf(f, "%d", &len) != 1)
            rc = WRONG_DATA;
        else {
            edges.fig_edges = (line*)malloc(len * sizeof(line));
            if (!edges.fig_edges)
                rc = MEM_ERR;
            else {
                edges.edges_count = len;

                i = 0;
                while ((!rc) && (i < len)) {
                    rc = import_edge(edges.fig_edges[i], f);

                    i++;
                }

                if ((feof(f)) && (i == len))
                    rc = OK;
                if ((!edges.dots_count) || (!edges.edges_count))
                    rc = EMPTY_FIGURE;
                if (rc) {
                    free(edges.fig_edges);
                    edges.fig_edges = NULL;
                }
            }
        }
    }

    if (rc) {
        free(edges.fig_dots);
        edges.fig_dots = NULL;
    }

    return rc;
}

int export_fig(FILE *f, fig_info &figure) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    int rc = export_all_dots(f, figure.fig_dots);

    rc = export_all_edges(f, figure.fig_edges);

    return rc;
}
