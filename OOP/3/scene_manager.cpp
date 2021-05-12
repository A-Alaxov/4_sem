#include "scene_manager.hpp"

scene_manager::scene_manager()
    :_scene(new scene)
{
}

std::shared_ptr<scene> scene_manager::get_scene()
{
    return _scene;
}
