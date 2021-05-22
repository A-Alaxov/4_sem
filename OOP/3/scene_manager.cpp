#include "scene_manager.hpp"

scene_manager::scene_manager()
    :_scene(new scene)
{
}

std::shared_ptr<scene> scene_manager::get_scene()
{
    return _scene;
}

std::shared_ptr<camera> scene_manager::get_camera()
{
    return _camera;
}

void scene_manager::set_camera(long number)
{
    if (_scene->get_cameras().size() < 1)
    {
        _camera = nullptr;
        return;
    }
    std::shared_ptr<camera> cam = _scene->get_cameras().at(number);
    _camera = cam;
}
