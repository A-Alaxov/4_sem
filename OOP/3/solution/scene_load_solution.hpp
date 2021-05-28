#ifndef SCENE_LOAD_SOLUTION_H
#define SCENE_LOAD_SOLUTION_H

#define SCENE_CFG_PATH "./data/scene_load.cfg"

#include "solution_manager.hpp"

class scene_load_solution
{
public:
    scene_load_solution() = default;

    std::shared_ptr<scene_loader_creator> get_creator();
};

#endif // SCENE_LOAD_SOLUTION_H
