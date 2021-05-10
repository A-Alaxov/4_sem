#include "controller.hpp"

controller::controller()
{

}

void controller::load_model(std::string name)
{
    loader->load_model(name);
}
