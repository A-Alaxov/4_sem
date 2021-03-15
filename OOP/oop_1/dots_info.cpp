#include "dot.h"
#include "dots_info.h"
#include "errors.h"
#include <cstdlib>
#include <cmath>

dots_info init_dots() {
    dots_info fig_dots;
    fig_dots.dots = NULL;
    fig_dots.count = 0;

    return fig_dots;
}

void free_dots(dots_info &fig_dots) {
    free(fig_dots.dots);
    fig_dots.count = 0;
}

int shift_all_dots(dots_info &fig_dots, shift_params &params) {
    if (!fig_dots.dots)
        return NO_DATA;

    for (int i = 0; i < fig_dots.count; i++) {
        shift_dot(fig_dots.dots[i], params);
    }

    return OK;
}

trig_funcs trig_init(double &angle) {
    trig_funcs funcs;
    funcs.sin = sin(angle);
    funcs.cos = cos(angle);

    return funcs;
}

int rotate_all_dots(dots_info &fig_dots, rotate_params &params) {
    if (!fig_dots.dots)
        return NO_DATA;

    dot opp_centre;
    get_opposite(opp_centre, params.centre);

    params.xy_angle = (params.xy_angle * M_PI) / 180;
    params.yz_angle = (params.yz_angle * M_PI) / 180;
    params.zx_angle = (params.zx_angle * M_PI) / 180;

    trig_angles angles;

    angles.xy_flat = trig_init(params.xy_angle);
    angles.yz_flat = trig_init(params.yz_angle);
    angles.zx_flat = trig_init(params.zx_angle);

    for (int i = 0; i < fig_dots.count; i++) {
        change_coord_sys(fig_dots.dots[i], params.centre);
        rotate_dot(fig_dots.dots[i], angles);
        change_coord_sys(fig_dots.dots[i], opp_centre);
    }

    return OK;
}

int scale_all_dots(dots_info &fig_dots, scale_params &params) {
    if (!fig_dots.dots)
        return NO_DATA;

    dot opp_centre;
    get_opposite(opp_centre, params.centre);

    for (int i = 0; i < fig_dots.count; i++) {
        change_coord_sys(fig_dots.dots[i], params.centre);
        scale_dot(fig_dots.dots[i], params.coefs);
        change_coord_sys(fig_dots.dots[i], opp_centre);
    }

    return OK;
}

int get_edge_dots(screen_edge &scr_edge, line &cur_edge, dots_info &fig_dots) {
    if (!fig_dots.dots)
        return NO_DATA;

    get_screen_dot(scr_edge.dot1, fig_dots.dots[cur_edge.dot1]);
    get_screen_dot(scr_edge.dot2, fig_dots.dots[cur_edge.dot2]);

    return OK;
}

int import_all_dots(dots_info &fig_dots, FILE *f) {
    int rc = OK;
    int len, i = 0;

    figure tmp_edges;

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

int export_all_dots(FILE *f, dots_info &fig_dots) {
    if (!fig_dots.dots)
        return NO_DATA;

    fprintf(f, "%d\n", fig_dots.count);

    for (int i = 0; i < fig_dots.count; i++) {
        export_dot(f, fig_dots.dots[i]);
    }

    return OK;
}
