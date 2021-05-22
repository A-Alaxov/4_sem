#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "controller.hpp"
#include "drawer.hpp"

class base_command
{
public:
    virtual ~base_command() = default;

    virtual void execute(std::shared_ptr<base_controller> &controller) = 0;
};

class load_model : public base_command
{
public:
    explicit load_model(std::string name) : name(name) {}
    void execute(std::shared_ptr<base_controller> &controller) override;

private:
    std::string name;
};

class add_camera : public base_command
{
public:
    explicit add_camera() {}
    void execute(std::shared_ptr<base_controller> &controller) override;
};

class draw_scene : public base_command
{
public:
    explicit draw_scene(std::shared_ptr<base_drawer> drawer) : drawer(drawer) {};
    void execute(std::shared_ptr<base_controller> &controller) override;

private:
    std::shared_ptr<base_drawer> drawer;
};

class reform_model : public base_command
{
public:
    explicit reform_model(long &index, point &shift, point &scale, point &rotate) : index(index), shift(shift), scale(scale), rotate(rotate) {};
    void execute(std::shared_ptr<base_controller> &controller) override;

private:
    long index;
    point shift;
    point scale;
    point rotate;
};

class reform_camera : public base_command
{
public:
    explicit reform_camera(long &index, point &shift, point &rotate) : index(index), shift(shift), rotate(rotate) {};
    void execute(std::shared_ptr<base_controller> &controller) override;

private:
    long index;
    point shift;
    point rotate;
};

class remove_model : public base_command
{
public:
    explicit remove_model(long &index) : index(index) {};
    void execute(std::shared_ptr<base_controller> &controller) override;

private:
    long index;
};

class remove_camera : public base_command
{
public:
    explicit remove_camera(long &index) : index(index) {};
    void execute(std::shared_ptr<base_controller> &controller) override;

private:
    long index;
};

#endif // COMMANDS_HPP
