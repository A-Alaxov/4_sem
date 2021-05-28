#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include <memory>
#include "visitor.hpp"
#include "scene.hpp"
#include "base_manager.hpp"

class draw_manager : public base_manager
{
public:
    draw_manager() = default;
    ~draw_manager() = default;

    void set_drawer(std::shared_ptr<base_drawer> _drawer);
    void set_camera(std::shared_ptr<camera> _camera);

    void draw(std::shared_ptr<scene> _scene);

private:
    std::shared_ptr<visitor> _visitor;
    std::shared_ptr<base_drawer> _drawer;
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
