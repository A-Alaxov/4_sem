#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "loader.hpp"

class base_controller
{
public:
    base_controller() = default;
    ~base_controller() = default;

    virtual void load_model(std::string name) = 0;
    virtual void add_model() = 0;
    virtual void remove_model() = 0;
    virtual void add_camera() = 0;
    virtual void set_camera() = 0;
    virtual void remove_camera() = 0;
    virtual void draw_scene() = 0;
    virtual void reform_model() = 0;
    virtual void reform_models() = 0;
    virtual void reform_camera() = 0;
};

class controller : public base_controller
{
public:
    controller();
    ~controller();

    void load_model(std::string name) override;
    void add_model() override;
    void remove_model() override;
    void add_camera() override;
    void set_camera() override;
    void remove_camera() override;
    void draw_scene() override;
    void reform_model() override;
    void reform_models() override;
    void reform_camera() override;

private:
    //scene_manager _scene_manager;
    //reform_manager _reform_manager;
    std::shared_ptr<base_loader> loader;
};

#endif // CONTROLLER_HPP
