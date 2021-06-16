#ifndef LOAD_MANAGER_HPP
#define LOAD_MANAGER_HPP

#include "object.hpp"
#include "secretary.hpp"
#include "base_manager.hpp"

class load_manager : public base_manager
{
public:
    load_manager() = default;
    std::shared_ptr<object> load(const std::string &name);
    std::shared_ptr<scene> load_scene(const std::string &name);
    void set_secretary(const std::shared_ptr<load_general_secretary> &secretary);
    void set_scene_secretary(const std::shared_ptr<scene_secretary> &secretary);

private:
    std::shared_ptr<load_general_secretary> secretary;
    std::shared_ptr<scene_secretary> scn_secr;
};

class load_manager_creator
{
public:
    std::shared_ptr<load_manager> get_manager();

private:
    void create_manager();

    std::shared_ptr<load_manager> _manager;
};

#endif // LOAD_MANAGER_HPP
