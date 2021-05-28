#include "fstream"
#include "scene_load_solution.hpp"
#include "errors.hpp"

std::shared_ptr<scene_loader_creator> scene_load_solution::get_creator()
{
    std::ifstream file(SCENE_CFG_PATH);

    if (!file)
    {
        std::string message = "Error in getting scene from config file";
        throw file_error(message);
    }

    size_t id;
    if (!(file >> id))
    {
        std::string message = "Error in getting scene from config file";
        throw file_error(message);
    }

    return solution_manager_creator().get_manager()->get_scene_creator(id);
}
