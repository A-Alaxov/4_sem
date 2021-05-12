#ifndef SCENE_HPP
#define SCENE_HPP

#include "composite.hpp"
#include "model.hpp"

class scene
{
public:
    scene();
    ~scene() = default;

    void add_model(std::shared_ptr<model> _model);
    void remove_model();

    //void add_camera();
    //void remove_camera();

    std::shared_ptr<composite> get_models() { return models; };

private:
    std::shared_ptr<composite> models;
    //std::shared_ptr<object> cameras;
};

#endif // SCENE_HPP
