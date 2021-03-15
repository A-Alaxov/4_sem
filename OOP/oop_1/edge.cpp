#include "edge.h"
#include "errors.h"

bool check_line(line &edge, int &count) {
    if ((edge.dot1 < 0) || (edge.dot1 >= count) ||
        (edge.dot2 < 0) || (edge.dot2 >= count))
        return false;
    else
        return true;
}

int import_edge(line &edge, FILE *f) {
    if (fscanf(f, "%d", &edge.dot1) != 1)
        return WRONG_DATA;
    if (fscanf(f, "%d", &edge.dot2) != 1)
        return WRONG_DATA;
    return OK;
}

int export_edge(FILE *f, line &edge) {
    fprintf(f, "%d %d\n", edge.dot1, edge.dot2);

    return OK;
}
