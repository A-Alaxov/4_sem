#ifndef SCENE_HPP
#define SCENE_HPP

#include "composite.hpp"
#include "model.hpp"
#include "camera.hpp"

class scene : public object
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

    virtual void accept(std::shared_ptr<visitor> _visitor) override { _visitor->visit_scene(*this); }
    virtual bool is_composite() override { return true; }
    virtual bool is_visible() override { return true; }
    virtual void reform(std::shared_ptr<Matrix<double>> reform_mtr) override;

private:
    std::shared_ptr<composite> models;
    std::shared_ptr<composite> cameras;
};

#endif // SCENE_HPP
