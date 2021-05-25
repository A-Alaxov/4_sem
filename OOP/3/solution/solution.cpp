#include "errors.hpp"
#include "solution.hpp"

bool solution::registration(size_t index, const std::shared_ptr<loader_creator> &lc)
{
    return callback.insert(callback_map::value_type(index, lc)).second;
}

std::shared_ptr<loader_creator> solution::get_creator(size_t index)
{
    callback_map::const_iterator it = callback.find(index);
    if (it == callback.end())
    {
        std::string message = "";
        throw config_error(message);
    }

    return it->second;
}
