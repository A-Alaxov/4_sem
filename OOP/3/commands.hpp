#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "controller.hpp"

class base_command
{
public:
    base_command() = default;
    ~base_command() = default;

    virtual void execute(std::shared_ptr<base_controller> controller) = 0;
};

class load_model : public base_command
{
public:
    explicit load_model(std::string name) : name(name) {}
    void execute(std::shared_ptr<base_controller> controller) override;

private:
    std::string name;
};

#endif // COMMANDS_HPP
