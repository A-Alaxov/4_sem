#include "secretary.hpp"
#include "solution.hpp"
#include "model_load_solution.hpp"
#include "camera_load_solution.hpp"
#include "scene_load_solution.hpp"

model_secretary::model_secretary()
{
    std::shared_ptr<loader_creator> cr = model_load_solution().get_creator();
    src_loader = std::shared_ptr<source_loader>(cr->create_loader());
}

std::shared_ptr<object> model_secretary::load(std::string name)
{
    src_loader->open(name);
    std::shared_ptr<object> _model = src_loader->load();
    src_loader->close();

    return _model;
}

camera_secretary::camera_secretary()
{
    std::shared_ptr<loader_creator> cr = camera_load_solution().get_creator();
    src_loader = std::shared_ptr<source_loader>(cr->create_loader());
}

std::shared_ptr<object> camera_secretary::load(std::string name)
{
    src_loader->open(name);
    std::shared_ptr<object> _camera = src_loader->load();
    src_loader->close();

    return _camera;
}

scene_secretary::scene_secretary()
{
    std::shared_ptr<loader_creator> cr = scene_load_solution().get_creator();
    src_loader = std::shared_ptr<source_loader>(cr->create_loader());
}

std::shared_ptr<object> scene_secretary::load(std::string name)
{
    src_loader->open(name);
    std::shared_ptr<object> _model = src_loader->load();
    src_loader->close();

    return _model;
}
