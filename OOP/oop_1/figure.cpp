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

int check_fig(const fig_info &figure) {
    int rc = check_edges(figure.fig_edges, figure.fig_dots.count);
    return rc;
}

int shift(fig_info &figure, const shift_params &params) {
    if (!figure.exist)
        return INCORRECT_FIG;
    int rc = check_fig(figure);
    if (rc)
        return rc;

    rc = shift_dots(figure.fig_dots, params);

    return rc;
}

int rotate(fig_info &figure, const rotate_params &params) {
    if (!figure.exist)
        return INCORRECT_FIG;
    int rc = check_fig(figure);
    if (rc)
        return rc;

    rc = rotate_dots(figure.fig_dots, params);

    return rc;
}

int scale(fig_info &figure, const scale_params &params) {
    if (!figure.exist)
        return INCORRECT_FIG;
    int rc = check_fig(figure);
    if (rc)
        return rc;

    rc = scale_dots(figure.fig_dots, params);

    return rc;
}

int get_screen_fig(screen_fig &scr_fig, const fig_info &figure) {
    if (!figure.exist)
        return INCORRECT_FIG;
    int rc = check_fig(figure);
    if (rc)
        return rc;

    rc = get_screen_edges(scr_fig.fig_edges, figure.fig_edges);

    if (!rc)
        rc = get_screen_dots(scr_fig.fig_dots, figure.fig_dots);

    return rc;
}

int import_fig(fig_info &figure, const char *file_name) {
    FILE *f = fopen(file_name, "r");

    if (!f)
        return WRONG_FILE_NAME;

    fig_info tmp_figure = init_fig();

    int rc = import_dots(tmp_figure.fig_dots, f);

    if (!rc) {
        rc = import_edges(tmp_figure.fig_edges, f);

        if (rc)
            free_dots(tmp_figure.fig_dots);
    }

    fclose(f);

    if (!rc) {
        rc = check_fig(tmp_figure);

        if (rc) {
            free_fig(tmp_figure);
        }
        else {
            tmp_figure.exist = true;
            free_fig(figure);
            figure = tmp_figure;
        }
    }

    return rc;
}

int export_fig(const char *file_name, const fig_info &figure) {
    if (!figure.exist)
        return INCORRECT_FIG;
    int rc = check_fig(figure);
    if (rc)
        return rc;

    FILE *f = fopen(file_name, "w");

    if (!f)
        return WRONG_FILE_NAME;

    rc = export_dots(f, figure.fig_dots);

    if (!rc)
        rc = export_edges(f, figure.fig_edges);

    fclose(f);

    return rc;
}
