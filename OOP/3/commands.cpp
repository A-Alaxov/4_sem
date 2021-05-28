#include "commands.hpp"
#include "point.hpp"
#include "transform_matrix.hpp"
#include "load_manager.hpp"
#include "draw_manager.hpp"
#include "reform_manager.hpp"
#include "scene_manager.hpp"

void load_model::execute()
{
    if (!scene_manager_creator().get_manager()->is_camera_exist())
    {
        std::string message = "There is no camera";
        throw no_camera_error(message);
    }

    std::shared_ptr<load_manager> _load_manager = load_manager_creator().get_manager();
    _load_manager->set_secretary(std::shared_ptr<load_general_secretary>(new model_secretary));
    std::shared_ptr<object> _model = _load_manager->load(name);
    scene_manager_creator().get_manager()->get_scene()->add_model(_model);
}

void load_camera::execute()
{
    std::shared_ptr<load_manager> _load_manager = load_manager_creator().get_manager();
    _load_manager->set_secretary(std::shared_ptr<load_general_secretary>(new camera_secretary));
    std::shared_ptr<object> _camera = _load_manager->load(name);
    scene_manager_creator().get_manager()->get_scene()->add_camera(_camera);
}

void load_scene::execute()
{
    std::shared_ptr<load_manager> _load_manager = load_manager_creator().get_manager();
    _load_manager->set_scene_secretary(std::shared_ptr<scene_secretary>());
    std::shared_ptr<object> _scene = _load_manager->load(name);
    scene_manager_creator().get_manager()->get_scene()->add_camera(_scene);
}

void draw_scene::execute()
{
    if (!scene_manager_creator().get_manager()->is_camera_exist())
    {
        std::string message = "There is no camera";
        throw no_camera_error(message);
    }

    draw_manager_creator().get_manager()->set_camera(scene_manager_creator().get_manager()->get_camera());
    draw_manager_creator().get_manager()->set_drawer(drawer);

    drawer->clear_scene();

    draw_manager_creator().get_manager()->draw(scene_manager_creator().get_manager()->get_scene());
}

void reform_model::execute()
{
    std::shared_ptr<object> _model = scene_manager_creator().get_manager()->get_scene()->get_models()->get_objects().at(index);
    reform_manager_creator().get_manager()->shift_model(_model, shift);
    reform_manager_creator().get_manager()->scale_model(_model, scale);
    reform_manager_creator().get_manager()->rotate_model(_model, rotate);
}

void reform_camera::execute()
{
    std::shared_ptr<object> _camera = scene_manager_creator().get_manager()->get_scene()->get_cameras()->get_objects().at(index);
    reform_manager_creator().get_manager()->shift_model(_camera, shift);

    std::shared_ptr<Matrix<double>> reform_mtr(std::make_shared<MoveMatrix>(rotate));
    scene_manager_creator().get_manager()->get_camera()->rotate(reform_mtr);
}

void remove_model::execute()
{
    scene_manager_creator().get_manager()->get_scene()->remove_model(index);
}

void remove_camera::execute()
{
    scene_manager_creator().get_manager()->get_scene()->remove_camera(index);
}

void set_camera::execute()
{
    scene_manager_creator().get_manager()->set_camera(index);
}
