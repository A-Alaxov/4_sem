#include "controller.hpp"
#include "transform_matrix.hpp"

controller::controller()
    :_drawer_manager(std::make_shared<draw_manager>())
{
    std::shared_ptr<source_loader> src_loader(std::make_shared<file_loader>());
    std::shared_ptr<base_builder> builder(std::make_shared<model_builder>());
    std::shared_ptr<base_model_loader> mdl_loader(std::make_shared<model_loader>(src_loader, builder));

    loader = mdl_loader;
}

void controller::load_model(std::string name)
{
    std::shared_ptr<model> model = loader->load_model(name);
    _scene_manager.get_scene()->add_model(model);
}

void controller::remove_model(long index)
{
    _scene_manager.get_scene()->remove_model(index);
}

void controller::draw_scene(std::shared_ptr<base_drawer> _drawer)
{
    _drawer->clear_scene();
    _drawer_manager->set_drawer(_drawer);
    _drawer_manager->set_camera(_scene_manager.get_camera());
    _scene_manager.get_scene()->get_models()->accept(_drawer_manager);
}

void controller::set_camera(long index)
{
    _scene_manager.set_camera(index);
}

void controller::remove_camera(long index)
{
    bool flag = false;
    if (_scene_manager.get_camera() == _scene_manager.get_scene()->get_cameras().at(index))
        flag = true;

    _scene_manager.get_scene()->remove_camera(index);

    if (flag)
    {
        set_camera(0);
    }
}

void controller::reform_model(long &model_index, point &move, point &scale, point &rotate)
{
    std::shared_ptr<object> model = _scene_manager.get_scene()->get_models()->get_objects().at(model_index);
    _reform_manager.shift_model(model, move);
    _reform_manager.scale_model(model, scale);
    _reform_manager.rotate_model(model, rotate);
}

void controller::reform_camera(long &camera_index, point &move, point &rotate)
{
    std::shared_ptr<object> camera = _scene_manager.get_scene()->get_cameras().at(camera_index);
    _reform_manager.shift_model(camera, move);

    std::shared_ptr<Matrix<double>> reform_mtr(std::make_shared<MoveMatrix>(rotate));
    _scene_manager.get_camera()->rotate(reform_mtr);
}

void controller::add_camera(point &cam_pos)
{
    std::shared_ptr<camera> cam(new camera);
    _reform_manager.shift_model(cam, cam_pos);

    _scene_manager.get_scene()->add_camera(cam);
    _scene_manager.set_camera(_scene_manager.get_scene()->get_cameras().size() - 1);
}
