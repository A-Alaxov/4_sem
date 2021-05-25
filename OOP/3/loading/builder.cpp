#include "builder.hpp"
#include "errors.hpp"

bool model_builder::is_build()
{
    return _details != nullptr;
}

void model_builder::build()
{
    _details.reset();
    _details = std::make_shared<details>();
}

void model_builder::build_points(std::vector<point> pts)
{
    if (!is_build())
    {
        std::string message = "Error while building point";
        throw file_error(message);
    }
    for (auto _point : pts)
        _details->add_point(_point);
}

void model_builder::build_edges(std::vector<edge> eds)
{
    if (!is_build())
    {
        std::string message = "Error while building edge";
        throw file_error(message);
    }
    for (auto _edge : eds)
        _details->add_edge(_edge);
}

std::shared_ptr<object> model_builder::get()
{
    return std::shared_ptr<model>(new model(_details));
}

void scene_builder::build()
{
    _scene = std::shared_ptr<scene>(new scene);
}

bool scene_builder::is_build()
{
    return _scene != nullptr;
}

std::shared_ptr<object> scene_builder::get()
{
    return std::dynamic_pointer_cast<object>(_scene);
}

void scene_builder::build_model(const std::shared_ptr<object> &_model)
{
    _scene->add_model(_model);
}

void scene_builder::build_camera(const std::shared_ptr<object> &_camera)
{
    _scene->add_camera(_camera);
}

void camera_builder::build()
{
    _camera = std::shared_ptr<camera>(new camera);
}

bool camera_builder::is_build()
{
    return _camera != nullptr;
}

std::shared_ptr<object> camera_builder::get()
{
    return std::dynamic_pointer_cast<object>(_camera);
}

void camera_builder::build_pos(double x, double y, double z)
{
    _camera->set_position(point(x, y, z));
}

void camera_builder::build_angles(double ox, double oy, double oz)
{
    _camera->set_angles(point(ox, oy, oz));
}
