#ifndef REFORM_MANAGER_HPP
#define REFORM_MANAGER_HPP

#include <object.hpp>
#include "point.hpp"

class reform_manager
{
public:
    void reform_model(std::shared_ptr<object> obj, point &move, point &scale, point &rotate);

private:
    point deg_to_rad(point &rotate);
};

#endif // REFORM_MANAGER_HPP
