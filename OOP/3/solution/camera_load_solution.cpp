#include "fstream"
#include "camera_load_solution.hpp"
#include "errors.hpp"

std::shared_ptr<loader_creator> camera_load_solution::get_creator()
{
    std::ifstream file(CAMERA_CFG_PATH);

    if (!file)
    {
        std::string message = "Error in getting camera from config file";
        throw file_error(message);
    }

    size_t id;
    if (!(file >> id))
    {
        std::string message = "Error in getting camera from config file";
        throw file_error(message);
    }

    return solution_manager_creator().get_manager()->get_creator(id);
}
