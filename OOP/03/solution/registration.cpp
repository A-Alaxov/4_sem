#include "errors.hpp"
#include "registration.hpp"
#include "model_file_loader.hpp"
#include "camera_file_loader.hpp"
#include "scene_file_loader.hpp"

void registration_maker::make_registration(solution &_solution)
{

    bool is_registered = _solution.registration_creator(0,
                          std::shared_ptr<loader_creator>(new con_loader_creator<model_file_loader>()));
    if (!is_registered)
    {
        std::string message = "";
        throw config_error(message);
    }

    is_registered = _solution.registration_creator(1,
                          std::shared_ptr<loader_creator>(new con_loader_creator<camera_file_loader>()));
    if (!is_registered)
    {
        std::string message = "";
        throw config_error(message);
    }

    is_registered = _solution.registration_scene_creator(2,
                          std::shared_ptr<scene_loader_creator>(new con_scene_loader_creator<scene_file_loader>()));
    if (!is_registered)
    {
        std::string message = "";
        throw config_error(message);
    }

    is_registered = _solution.registration_factory(0,
                          std::shared_ptr<abstract_factory>(new qt_factory()));
    if (!is_registered)
    {
        std::string message = "";
        throw config_error(message);
    }
}
