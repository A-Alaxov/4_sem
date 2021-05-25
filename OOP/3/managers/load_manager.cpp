#include "load_manager.hpp"
#include "errors.hpp"

std::shared_ptr<object> load_manager::load(const std::string &name)
{
    if (secretary == nullptr)
    {
        std::string message = "Error in loading";
        throw no_secretary_error(message);
    }

    return secretary->load(name);
}

void load_manager::set_secretary(const std::shared_ptr<load_general_secretary> &secretary)
{
    this->secretary = secretary;
}

std::shared_ptr<load_manager> load_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void load_manager_creator::create_manager()
{
    static std::shared_ptr<load_manager> _manager(new load_manager());
    this->_manager = _manager;
}
