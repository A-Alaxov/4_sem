#include "drawer_solution.hpp"

std::shared_ptr<abstract_factory> drawer_solution::get_factory()
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

    return solution_manager_creator().get_manager()->get_factory(id);
}
