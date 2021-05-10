#include "commands.hpp"

void load_model::execute(std::shared_ptr<base_controller> controller)
{
    controller->load_model(name);
}
