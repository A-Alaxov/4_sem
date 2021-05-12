#include "reform_manager.hpp"
#include <math.h>

void reform_manager::reform_model(std::shared_ptr<object> obj, point &move, point &scale, point &rotate)
{
    obj->reform(move, scale, rotate);
}

point reform_manager::deg_to_rad(point &rotate)
{
    point radians(rotate);
    radians.set_x(rotate.get_x() * M_PI / 180);
    radians.set_x(rotate.get_y() * M_PI / 180);
    radians.set_x(rotate.get_z() * M_PI / 180);

    return radians;
}
