#include "facade.hpp"
#include "creator.hpp"

facade::facade()
{
    std::shared_ptr<creator> cr(new con_creator<controller>());
    _controller = cr->get_product();
}

facade::~facade()
{
    _controller.reset();
}

void facade::execute_command(std::shared_ptr<base_command> command)
{
    command->execute(_controller);
}
