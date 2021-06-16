#include "solution_manager.hpp"

std::shared_ptr<solution_manager> solution_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void solution_manager_creator::create_manager()
{
    static std::shared_ptr<solution_manager> _manager(new solution_manager());
    this->_manager = _manager;
}

solution_manager::solution_manager()
    :reg_maker(std::shared_ptr<base_registration_maker>(new registration_maker()))
{
    reg_maker->make_registration(_solution);
}


std::shared_ptr<loader_creator> solution_manager::get_creator(size_t index)
{
    return _solution.get_creator(index);
}

std::shared_ptr<scene_loader_creator> solution_manager::get_scene_creator(size_t index)
{
    return _solution.get_scene_creator(index);
}

std::shared_ptr<abstract_factory> solution_manager::get_factory(size_t index)
{
    return _solution.get_factory(index);
}
