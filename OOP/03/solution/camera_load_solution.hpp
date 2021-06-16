#ifndef CAMERA_LOAD_SOLUTION_H
#define CAMERA_LOAD_SOLUTION_H

#define CAMERA_CFG_PATH "./data/camera_load.cfg"

#include "solution_manager.hpp"

class camera_load_solution
{
public:
    camera_load_solution() = default;

    std::shared_ptr<loader_creator> get_creator();
};

#endif // CAMERA_LOAD_SOLUTION_H
