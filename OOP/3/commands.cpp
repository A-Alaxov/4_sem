#include "commands.hpp"
#include "point.hpp"

void load_model::execute(std::shared_ptr<base_controller> &controller)
{
    controller->load_model(name);
}

void add_camera::execute(std::shared_ptr<base_controller> &controller)
{
    point pos(0, 0, 300);
    controller->add_camera(pos);
}

void draw_scene::execute(std::shared_ptr<base_controller> &controller)
{
    controller->draw_scene(drawer);
}

void reform_model::execute(std::shared_ptr<base_controller> &controller)
{
    controller->reform_model(index, shift, scale, rotate);
}

void reform_camera::execute(std::shared_ptr<base_controller> &controller)
{
    controller->reform_camera(index, shift, rotate);
}

void remove_model::execute(std::shared_ptr<base_controller> &controller)
{
    controller->remove_model(index);
}

void remove_camera::execute(std::shared_ptr<base_controller> &controller)
{
    controller->remove_camera(index);
}
