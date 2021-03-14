#include "dot_funcs.h"
#include "figure_funcs.h"
#include "errors.h"
#include <cstdlib>
#include <cmath>

int shift(figure &edges, shift_params &params) {
    if ((!edges.fig_dots) || (!edges.fig_edges))
        return NO_DATA;

    for (int i = 0; i < edges.dots_count; i++) {
        shift_dot(edges.fig_dots[i], params);
    }

    return OK;
}

int rotate(figure &edges, rotate_params &params) {
    if ((!edges.fig_dots) || (!edges.fig_edges))
        return NO_DATA;

    dot opp_centre;
    get_opposite(opp_centre, params.centre);

    params.xy_angle = (params.xy_angle * M_PI) / 180;
    params.yz_angle = (params.yz_angle * M_PI) / 180;
    params.zx_angle = (params.zx_angle * M_PI) / 180;

    trig_angles angles = { sin(params.xy_angle), cos(params.xy_angle),
                           sin(params.yz_angle), cos(params.yz_angle),
                           sin(params.zx_angle), cos(params.zx_angle) };

    for (int i = 0; i < edges.dots_count; i++) {
        change_coord_sys(edges.fig_dots[i], params.centre);
        rotate_dot(edges.fig_dots[i], angles);
        change_coord_sys(edges.fig_dots[i], opp_centre);
    }

    return OK;
}

int scale(figure &edges, scale_params &params) {
    if ((!edges.fig_dots) || (!edges.fig_edges))
        return NO_DATA;

    dot opp_centre;
    get_opposite(opp_centre, params.centre);

    for (int i = 0; i < edges.dots_count; i++) {
        change_coord_sys(edges.fig_dots[i], params.centre);
        scale_dot(edges.fig_dots[i], params.coefs);
        change_coord_sys(edges.fig_dots[i], opp_centre);
    }

    return OK;
}

int get_edge(screen_edge &scr_edge, figure &edges) {
    if ((!edges.fig_dots) || (!edges.fig_edges))
        return NO_DATA;

    if (scr_edge.number >= edges.edges_count)
        return WRONG_INDEX;

    line cur_edge = edges.fig_edges[scr_edge.number];

    change_dot(scr_edge.dot1, edges.fig_dots[cur_edge.dot1]);
    change_dot(scr_edge.dot2, edges.fig_dots[cur_edge.dot2]);

    return OK;
}

int import_fig(figure &edges, FILE *f) {
    int rc = OK;
    int len, i = 0;

    free(edges.fig_dots);
    free(edges.fig_edges);

    if (fscanf(f, "%d", &len) != 1)
        return WRONG_DATA;

    edges.fig_dots = (dot*)malloc(len * sizeof(dot));
    if (!edges.fig_dots)
        return MEM_ERR;
    else {
        edges.dots_count = len;

        while ((!rc) && (i < len)) {
            rc = import_dot(edges.fig_dots[i], f);

            i++;
        }

        if (!rc) {
            if (fscanf(f, "%d", &len) != 1)
                rc = WRONG_DATA;
            else {
                edges.fig_edges = (line*)malloc(len * sizeof(line));
                if (!edges.fig_dots)
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
    }

    if (rc) {
        free(edges.fig_dots);
        edges.fig_dots = NULL;
    }

    return rc;
}

int export_fig(FILE *f, figure &edges) {
    if ((!edges.fig_dots) || (!edges.fig_edges))
        return NO_DATA;

    fprintf(f, "%d\n", edges.dots_count);

    for (int i = 0; i < edges.dots_count; i++) {
        export_dot(f, edges.fig_dots[i]);
    }

    fprintf(f, "%d\n", edges.edges_count);

    for (int i = 0; i < edges.edges_count; i++) {
        export_edge(f, edges.fig_edges[i]);
    }

    return OK;
}
