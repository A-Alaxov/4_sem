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

class draw_scene : public base_command
{
public:
    explicit draw_scene(std::shared_ptr<base_drawer> drawer) : drawer(drawer) {};
    void execute(std::shared_ptr<base_controller> &controller) override;

private:
    std::shared_ptr<base_drawer> drawer;
};

#endif // COMMANDS_HPP
