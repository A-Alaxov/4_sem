#include "main_func.h"
#include "figure_funcs.h"
#include "errors.h"

int main_func(parametrs &params, operations func) {
    static figure edges = { NULL, NULL, 0, 0 };
    int rc = OK;

    if (func == SHIFT) {
        rc = shift(edges, params.shift);
    }
    if (func == ROTATE) {
        rc = rotate(edges, params.rotate);
    }
    if (func == SCALE) {
        rc = scale(edges, params.scale);
    }
    if (func == GET_EDGE) {
        rc = get_edge(params.edge, edges);
    }
    if (func == IMPORT) {
        rc = import_fig(edges, params.f);
    }
    if (func == EXPORT) {
        rc = export_fig(params.f, edges);
    }

    return rc;
}
