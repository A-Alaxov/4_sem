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

bool check_fig(const fig_info &figure) {
    if ((figure.exist) && (check_edges(figure.fig_edges, figure.fig_dots.count)))
        return true;
    else
        return false;
}

int shift(fig_info &figure, const shift_params &params) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    int rc = shift_all_dots(figure.fig_dots, params);

    return rc;
}

int rotate(fig_info &figure, const rotate_params &params) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    int rc = rotate_all_dots(figure.fig_dots, params);

    return rc;
}

int scale(fig_info &figure, const scale_params &params) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    int rc = scale_all_dots(figure.fig_dots, params);

    return rc;
}

int get_screen_edge(screen_edge &scr_edge, const fig_info &figure) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    line cur_line;

    int rc = get_cur_line(cur_line, scr_edge.number, figure.fig_edges);

    if (!rc)
        rc = get_edge_dots(scr_edge.dot1, cur_line.dot1, figure.fig_dots);
    if (!rc)
        rc = get_edge_dots(scr_edge.dot2, cur_line.dot2, figure.fig_dots);

    return rc;
}

int import_fig(fig_info &figure, const char *file_name) {
    int rc = OK;

    FILE *f = fopen(file_name, "r");

    if (!f)
        return WRONG_FILE_NAME;

    fig_info tmp_figure = init_fig();

    rc = import_all_dots(tmp_figure.fig_dots, f);

    if (!rc) {
        rc = import_all_edges(tmp_figure.fig_edges, f);

        if (rc)
            free_dots(tmp_figure.fig_dots);
    }

    fclose(f);

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

    return rc;
}

int export_fig(const char *file_name, const fig_info &figure) {
    if (!check_fig(figure))
        return INCORRECT_FIG;

    FILE *f = fopen(file_name, "w");

    if (!f)
        return WRONG_FILE_NAME;

    int rc = export_all_dots(f, figure.fig_dots);

    rc = export_all_edges(f, figure.fig_edges);

    fclose(f);

    return rc;
}
