#include "facade.hpp"

void facade::execute_command(std::shared_ptr<base_command> command)
{
    command->execute();
}
