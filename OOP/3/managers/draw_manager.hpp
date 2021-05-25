#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include <memory>
#include "visitor.hpp"
#include "drawer.hpp"
#include "scene.hpp"
#include "base_manager.hpp"

class draw_manager : public visitor, public base_manager
{
public:
    draw_manager() = default;
    ~draw_manager() = default;

    void set_drawer(std::shared_ptr<base_drawer> drawer);
    void set_camera(std::shared_ptr<camera> _camera);

    void visit_model(model &_model) override;
    void visit_camera(camera &_camera) override {};
    void visit_composite(composite &_composite) override {};
    void visit_scene(scene &_scene) override {};

private:
    point get_projection(point &_point);
    std::shared_ptr<base_drawer> drawer;
    std::shared_ptr<camera> _camera;
};

class draw_manager_creator
{
public:
    std::shared_ptr<draw_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<draw_manager> _manager;
};

#endif // DRAW_MANAGER_HPP
