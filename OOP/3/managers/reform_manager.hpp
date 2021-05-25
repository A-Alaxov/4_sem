#ifndef REFORM_MANAGER_HPP
#define REFORM_MANAGER_HPP

#include <object.hpp>
#include "point.hpp"
#include "base_manager.hpp"

class reform_manager : public base_manager
{
public:
    void shift_model(std::shared_ptr<object> obj, point &move);
    void scale_model(std::shared_ptr<object> obj, point &scale);
    void rotate_model(std::shared_ptr<object> obj, point &rotate);
};

class reform_manager_creator
{
public:
    std::shared_ptr<reform_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<reform_manager> _manager;
};

#endif // REFORM_MANAGER_HPP
