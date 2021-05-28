#include "errors.hpp"
#include "solution.hpp"

bool solution::registration_creator(size_t index, const std::shared_ptr<loader_creator> &lc)
{
    return creator_map.insert(callback_creator::value_type(index, lc)).second;
}

bool solution::registration_scene_creator(size_t index, const std::shared_ptr<scene_loader_creator> &lc)
{
    return scene_map.insert(callback_scene_creator::value_type(index, lc)).second;
}

bool solution::registration_factory(size_t index, const std::shared_ptr<abstract_factory> &lc)
{
    return factory_map.insert(callback_factory::value_type(index, lc)).second;
}

std::shared_ptr<loader_creator> solution::get_creator(size_t index)
{
    callback_creator::const_iterator it = creator_map.find(index);
    if (it == creator_map.end())
    {
        std::string message = "";
        throw config_error(message);
    }

    return it->second;
}

std::shared_ptr<scene_loader_creator> solution::get_scene_creator(size_t index)
{
    callback_scene_creator::const_iterator it = scene_map.find(index);
    if (it == scene_map.end())
    {
        std::string message = "";
        throw config_error(message);
    }

    return it->second;
}

std::shared_ptr<abstract_factory> solution::get_factory(size_t index)
{
    callback_factory::const_iterator it = factory_map.find(index);
    if (it == factory_map.end())
    {
        std::string message = "";
        throw config_error(message);
    }

    return it->second;
}
