#include "point.hpp"

#include <vector>
#include <math.h>

point::point()
{

}

point::point(const double x, const double y, const double z)
    :x(x), y(y), z(z)
{
}

void point::reform(const std::shared_ptr<Matrix<double>> mtr)
{
    std::vector<double> result(4, 0);
    std::vector<double> data = {x, y, z, 1.0};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i] += data[j] * (*mtr)[i][j];
        }
    }

    set_x(result[0]);
    set_y(result[1]);
    set_z(result[2]);
}

point point::deg_to_rad() const
{
    point radians(x, y, z);
    radians.set_x(x * M_PI / 180);
    radians.set_y(y * M_PI / 180);
    radians.set_z(z * M_PI / 180);

    return radians;
}
