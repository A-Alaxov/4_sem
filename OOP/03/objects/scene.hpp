#ifndef SCENE_HPP
#define SCENE_HPP

#include "composite.hpp"
#include "model.hpp"
#include "camera.hpp"

class scene
{
public:
    scene();
    ~scene() = default;

    void add_model(std::shared_ptr<object> _model);
    void remove_model(long index);

    void add_camera(std::shared_ptr<object> _camera);
    void remove_camera(long index);

    std::shared_ptr<composite> get_models() { return models; }
    std::shared_ptr<composite> get_cameras() { return cameras; }

private:
    std::shared_ptr<composite> models;
    std::shared_ptr<composite> cameras;
};

#endif // SCENE_HPP
