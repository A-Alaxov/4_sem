#include "entry.h"
#include "figure.h"
#include "errors.h"

int entry(parametrs &params, operations func) {
    static fig_info edges = init_fig();
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
        rc = get_screen_edge(params.edge, edges);
    }
    if (func == IMPORT) {
        rc = import_fig(edges, params.f);
    }
    if (func == EXPORT) {
        rc = export_fig(params.f, edges);
    }

    return rc;
}
