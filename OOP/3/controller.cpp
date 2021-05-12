#include "controller.hpp"

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

void controller::draw_scene(std::shared_ptr<base_drawer> _drawer)
{
    _drawer->clear_scene();
    _drawer_manager->set_drawer(_drawer);
    //_drawer_manager->set_cam(_scene_manager.get_cam());
    _scene_manager.get_scene()->get_models()->accept(_drawer_manager);
}
