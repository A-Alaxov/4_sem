#include "fstream"
#include "model_load_solution.hpp"
#include "errors.hpp"

std::shared_ptr<loader_creator> model_load_solution::get_creator()
{
    std::ifstream file(MODEL_CFG_PATH);

    if (!file)
    {
        std::string message = "Error in getting model from config file";
        throw file_error(message);
    }

    size_t id;
    if (!(file >> id))
    {
        std::string message = "Error in getting model from config file";
        throw file_error(message);
    }

    return solution_manager_creator().get_manager()->get_creator(id);
}
