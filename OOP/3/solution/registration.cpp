#include "errors.hpp"
#include "registration.hpp"
#include "source_loader.hpp"

void registration_maker::make_registration(solution &_solution)
{

    bool is_registered = _solution.registration(0,
                          std::shared_ptr<loader_creator>(new con_loader_creator<model_file_loader>()));
    if (!is_registered)
    {
        std::string message = "";
        throw config_error(message);
    }

    is_registered = _solution.registration(1,
                          std::shared_ptr<loader_creator>(new con_loader_creator<camera_file_loader>()));
    if (!is_registered)
    {
        std::string message = "";
        throw config_error(message);
    }

    is_registered = _solution.registration(2,
                          std::shared_ptr<loader_creator>(new con_loader_creator<scene_file_loader>()));
    if (!is_registered)
    {
        std::string message = "";
        throw config_error(message);
    }
}
