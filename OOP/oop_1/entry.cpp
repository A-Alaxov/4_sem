#include "entry.h"
#include "figure.h"
#include "errors.h"

int entry(parametrs &params, const operations func) {
    static fig_info figure = init_fig();
    int rc = OK;

    if (func == SHIFT) {
        rc = shift(figure, params.shift);
    }
    if (func == ROTATE) {
        rc = rotate(figure, params.rotate);
    }
    if (func == SCALE) {
        rc = scale(figure, params.scale);
    }
    if (func == GET_EDGE) {
        rc = get_screen_edge(params.edge, figure);
    }
    if (func == IMPORT) {
        rc = import_fig(figure, params.file_name);
    }
    if (func == EXPORT) {
        rc = export_fig(params.file_name, figure);
    }
    if (func == FREE) {
        free_fig(figure);
    }

    return rc;
}
