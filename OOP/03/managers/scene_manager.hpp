#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "scene.hpp"
#include "base_manager.hpp"

class scene_manager : public base_manager
{
public:
    scene_manager();
    ~scene_manager() = default;

    std::shared_ptr<scene> get_scene();
    void set_scene(std::shared_ptr<scene> _scene);

    std::shared_ptr<camera> get_camera();
    void set_camera(long cam_index);

    bool is_camera_exist() { return _camera != nullptr; }

private:
    std::shared_ptr<scene> _scene;
    std::shared_ptr<camera> _camera;
};

class scene_manager_creator
{
public:
    std::shared_ptr<scene_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<scene_manager> _manager;
};

#endif // SCENE_MANAGER_HPP
