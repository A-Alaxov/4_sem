#include "main_func.h"
#include "figure_funcs.h"
#include "errors.h"

int main_func(operations func, parametrs &params) {
    static figure edges;
    int rc = OK;

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
    if (func == IMPORT) {
        rc = import_fig(edges, params.f);
    }
    if (func == EXPORT) {
        export_fig(edges, params.f);
    }

    return rc;
}
