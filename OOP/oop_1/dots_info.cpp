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

int shift_dots(dots_info &fig_dots, const shift_params &params) {
    if (!fig_dots.dots)
        return NO_DATA;

    for (int i = 0; i < fig_dots.count; i++) {
        shift_dot(fig_dots.dots[i], params);
    }

    return OK;
}

trig_funcs trig_init(const double &angle) {
    double degr_angle = (angle * M_PI) / 180;

    trig_funcs funcs;
    funcs.sin = sin(degr_angle);
    funcs.cos = cos(degr_angle);

    return funcs;
}

int rotate_dots(dots_info &fig_dots, const rotate_params &params) {
    if (!fig_dots.dots)
        return NO_DATA;

    dot opp_centre;
    get_opposite(opp_centre, params.centre);

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

int scale_dots(dots_info &fig_dots, const scale_params &params) {
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

int screen_dots_alloc(screen_dots &fig_dots, const int &count) {
    screen_dot *tmp_dots = (screen_dot*)malloc(count * sizeof(screen_dot));
    if (!tmp_dots)
        return MEM_ERR;

    fig_dots.dots = tmp_dots;
    fig_dots.count = count;
    return OK;
}

int get_screen_dots(screen_dots &scr_dots, const dots_info &fig_dots) {
    int rc = screen_dots_alloc(scr_dots, fig_dots.count);

    for (int i = 0; (!rc) && (i < fig_dots.count); i++) {
        rc = get_screen_dot(scr_dots.dots[i], fig_dots.dots[i]);
    }

    return rc;
}

int scan_dots_count(int &count, FILE *const f) {
    if (fscanf(f, "%d", &count) != 1)
        return WRONG_DATA;

    return OK;
}

int dots_alloc(dots_info &fig_dots, const int &count) {
    dot *tmp_dots = (dot*)malloc(count * sizeof(dot));
    if (!tmp_dots)
        return MEM_ERR;

    fig_dots.dots = tmp_dots;
    fig_dots.count = count;
    return OK;
}

int import_dots(dots_info &fig_dots, FILE *const f) {
    int count;

    int rc = scan_dots_count(count, f);
    if (rc)
        return rc;

    rc = dots_alloc(fig_dots, count);
    if (rc)
        return rc;

    for (int i = 0; (!rc) && (i < fig_dots.count); i++) {
        rc = import_dot(fig_dots.dots[i], f);
    }

    if (rc)
        free_dots(fig_dots);

    return rc;
}

int export_dots(FILE *const f, const dots_info &fig_dots) {
    if (!fig_dots.dots)
        return NO_DATA;

    fprintf(f, "%d\n", fig_dots.count);

    for (int i = 0; i < fig_dots.count; i++) {
        export_dot(f, fig_dots.dots[i]);
    }

    return OK;
}
