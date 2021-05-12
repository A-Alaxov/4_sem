#include "point.hpp"
#include <math.h>

point::point()
{

}

point::point(const double x, const double y, const double z)
    :x(x), y(y), z(z)
{
}

void point::move(point &move)
{
    x += move.x;
    y += move.y;
    z += move.z;
}

void point::scale(point &scale)
{
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;
}

void point::rotate_in_flat(double &coord_1, double &coord_2, double &angle)
{
    double tmp_1 = coord_1;
    double tmp_2 = coord_2;

    coord_1 = tmp_1 * cos(angle) - tmp_2 * sin(angle);
    coord_2 = tmp_1 * sin(angle) + tmp_2 * cos(angle);
}

void point::rotate(point &rotate)
{
    rotate_in_flat(x, y, rotate.x);
    rotate_in_flat(y, z, rotate.y);
    rotate_in_flat(z, x, rotate.z);
}
