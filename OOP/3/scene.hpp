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

    void add_model(std::shared_ptr<model> _model);
    void remove_model(long index);

    void add_camera(std::shared_ptr<camera> _camera);
    void remove_camera(long index);

    std::shared_ptr<composite> get_models() { return models; };
    //std::shared_ptr<composite> get_cameras() { return cameras; };
    std::vector<std::shared_ptr<camera>> get_cameras() { return cameras; };
    //std::shared_ptr<model> get_model();

private:
    std::shared_ptr<composite> models;
    //std::shared_ptr<composite> cameras;
    std::vector<std::shared_ptr<camera>> cameras;
};

#endif // SCENE_HPP
