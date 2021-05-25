#ifndef SOLUTION_MANAGER_HPP
#define SOLUTION_MANAGER_HPP

#include "solution.hpp"
#include "registration.hpp"
#include "base_manager.hpp"

class solution_manager : public base_manager
{
public:
    solution_manager();

    std::shared_ptr<loader_creator> get_creator(size_t index);

private:
    solution _solution;
    std::shared_ptr<base_registration_maker> reg_maker;
};

class solution_manager_creator
{
public:
    std::shared_ptr<solution_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<solution_manager> _manager;
};

#endif // SOLUTION_MANAGER_HPP
