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
    fig_dots.dots = NULL;
    fig_dots.count = 0;
}

int shift_all_dots(dots_info &fig_dots, const shift_params &params) {
    if (!fig_dots.dots)
        return NO_DATA;

    for (int i = 0; i < fig_dots.count; i++) {
        shift_dot(fig_dots.dots[i], params);
    }

    return OK;
}

trig_funcs trig_init(const double &angle) {
    trig_funcs funcs;
    funcs.sin = sin(angle);
    funcs.cos = cos(angle);

    return funcs;
}

int rotate_all_dots(dots_info &fig_dots, const rotate_params &params) {
    if (!fig_dots.dots)
        return NO_DATA;

    dot opp_centre;
    get_opposite(opp_centre, params.centre);

    trig_angles angles;

    double cur_angle = (params.xy_angle * M_PI) / 180;
    angles.xy_flat = trig_init(cur_angle);

    cur_angle = (params.yz_angle * M_PI) / 180;
    angles.yz_flat = trig_init(cur_angle);

    cur_angle = (params.zx_angle * M_PI) / 180;
    angles.zx_flat = trig_init(cur_angle);

    for (int i = 0; i < fig_dots.count; i++) {
        change_coord_sys(fig_dots.dots[i], params.centre);
        rotate_dot(fig_dots.dots[i], angles);
        change_coord_sys(fig_dots.dots[i], opp_centre);
    }

    return OK;
}

int scale_all_dots(dots_info &fig_dots, const scale_params &params) {
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

int get_edge_dots(dot &scr_dot, const int &number, const dots_info &fig_dots) {
    if (!fig_dots.dots)
        return NO_DATA;

    get_screen_dot(scr_dot, fig_dots.dots[number]);

    return OK;
}

int import_all_dots(dots_info &fig_dots, FILE *const f) {
    int rc = OK;
    int i = 0;

    if (fscanf(f, "%d", &(fig_dots.count)) != 1)
        return WRONG_DATA;

    fig_dots.dots = (dot*)malloc(fig_dots.count * sizeof(dot));
    if (!fig_dots.dots)
        return MEM_ERR;

    while ((!rc) && (i < fig_dots.count)) {
        rc = import_dot(fig_dots.dots[i], f);

        i++;
    }

    if (rc)
        free_dots(fig_dots);

    return rc;
}

int export_all_dots(FILE *const f, const dots_info &fig_dots) {
    if (!fig_dots.dots)
        return NO_DATA;

    fprintf(f, "%d\n", fig_dots.count);

    for (int i = 0; i < fig_dots.count; i++) {
        export_dot(f, fig_dots.dots[i]);
    }

    return OK;
}
