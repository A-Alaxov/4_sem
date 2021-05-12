#include "drawer_factory.hpp"

std::shared_ptr<base_drawer> qt_factory::create_ui() const
{
    return std::make_shared<qt_drawer>();
}
