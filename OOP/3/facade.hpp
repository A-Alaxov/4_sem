#ifndef FACADE_HPP
#define FACADE_HPP

#include "commands.hpp"

class facade
{
public:
    facade();
    ~facade();

    void execute_command(std::shared_ptr<base_command> command);

private:
    std::shared_ptr<base_controller> controller;
};

#endif // FACADE_HPP
