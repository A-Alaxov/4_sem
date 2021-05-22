#ifndef REFORM_MANAGER_HPP
#define REFORM_MANAGER_HPP

#include <object.hpp>
#include "point.hpp"

class reform_manager
{
public:
    void shift_model(std::shared_ptr<object> obj, point &move);
    void scale_model(std::shared_ptr<object> obj, point &scale);
    void rotate_model(std::shared_ptr<object> obj, point &rotate);
};

#endif // REFORM_MANAGER_HPP
