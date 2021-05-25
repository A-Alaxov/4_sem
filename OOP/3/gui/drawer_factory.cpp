#include "drawer_factory.hpp"

std::shared_ptr<base_drawer> qt_factory::create_ui() const
{
    return std::shared_ptr<base_drawer>(new qt_drawer(_scene));
}
