#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "scene.hpp"

class scene_manager
{
public:
    scene_manager();
    ~scene_manager() = default;

    std::shared_ptr<scene> get_scene();
    void set_scene(std::shared_ptr<scene> _scene);

    std::shared_ptr<camera> get_camera();
    void set_camera(long cam_index);

private:
    std::shared_ptr<scene> _scene;
    std::shared_ptr<camera> _camera;
};

#endif // SCENE_MANAGER_HPP
