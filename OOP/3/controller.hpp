#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "model_loader.hpp"
#include "scene_manager.hpp"
#include "draw_manager.hpp"
#include "reform_manager.hpp"

class base_controller
{
public:
    ~base_controller() = default;

    virtual void load_model(std::string name) = 0;
    virtual void remove_model(long index) = 0;
    virtual void add_camera(point &cam_pos) = 0;
    virtual void set_camera(long index) = 0;
    virtual void remove_camera(long index) = 0;
    virtual void draw_scene(std::shared_ptr<base_drawer> _drawer) = 0;
    virtual void reform_model(long &model_index, point &move, point &scale, point &rotate) = 0;
    virtual void reform_camera(long &camera_index, point &move, point &rotate) = 0;
};

class controller : public base_controller
{
public:
    controller();
    ~controller() = default;

    void load_model(std::string name) override;
    void remove_model(long index) override;
    void add_camera(point &cam_pos) override;
    void set_camera(long index) override;
    void remove_camera(long index) override;
    void draw_scene(std::shared_ptr<base_drawer> _drawer) override;
    void reform_model(long &model_index, point &move, point &scale, point &rotate) override;
    void reform_camera(long &camera_index, point &move, point &rotate) override;

private:
    scene_manager _scene_manager;
    reform_manager _reform_manager;
    std::shared_ptr<base_model_loader> loader;
    std::shared_ptr<draw_manager> _drawer_manager;
};

#endif // CONTROLLER_HPP
