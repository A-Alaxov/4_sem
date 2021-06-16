#ifndef SOLUTION_H
#define SOLUTION_H

#include <map>
#include "loaders.hpp"
#include "drawer_factory.hpp"

class solution
{
public:
    solution() = default;
    ~solution() = default;

    bool registration_creator(size_t index, const std::shared_ptr<loader_creator> &lc);
    bool registration_scene_creator(size_t index, const std::shared_ptr<scene_loader_creator> &lc);
    bool registration_factory(size_t index, const std::shared_ptr<abstract_factory> &lc);
    std::shared_ptr<loader_creator> get_creator(size_t index);
    std::shared_ptr<scene_loader_creator> get_scene_creator(size_t index);
    std::shared_ptr<abstract_factory> get_factory(size_t index);

private:
    using callback_creator = std::map<size_t, std::shared_ptr<loader_creator>>;
    using callback_scene_creator = std::map<size_t, std::shared_ptr<scene_loader_creator>>;
    using callback_factory = std::map<size_t, std::shared_ptr<abstract_factory>>;
    callback_creator creator_map;
    callback_scene_creator scene_map;
    callback_factory factory_map;
};

#endif // SOLUTION_H
