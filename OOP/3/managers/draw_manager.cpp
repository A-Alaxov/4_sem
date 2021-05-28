#include "draw_manager.hpp"
#include "errors.hpp"
#include "transform_matrix.hpp"
#include <math.h>

std::shared_ptr<draw_manager> draw_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void draw_manager_creator::create_manager()
{
    static std::shared_ptr<draw_manager> _manager(new draw_manager());
    this->_manager = _manager;
}

void draw_manager::set_drawer(std::shared_ptr<base_drawer> _drawer)
{
    this->_drawer = _drawer;
}

void draw_manager::set_camera(std::shared_ptr<camera> _camera)
{
    this->_camera = _camera;
}

void draw_manager::draw(std::shared_ptr<scene> _scene)
{
    _scene->get_models()->accept(std::shared_ptr<visitor>(new visitor(_camera, _drawer)));
}
