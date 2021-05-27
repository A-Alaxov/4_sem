#ifndef DRAWER_SOLUTION_HPP
#define DRAWER_SOLUTION_HPP

#define SCENE_CFG_PATH "./data/drawer.cfg"

#include "solution_manager.hpp"

class drawer_solution
{
public:
    drawer_solution() = default;

    std::shared_ptr<abstract_factory> get_factory();
};

#endif // DRAWER_SOLUTION_HPP
