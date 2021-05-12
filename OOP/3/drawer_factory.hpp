#ifndef ABSTRACT_FACTORY_HPP
#define ABSTRACT_FACTORY_HPP

#include <memory>
#include "drawer.hpp"

class abstract_factory
{
public:
    virtual std::shared_ptr<base_drawer> create_ui() const = 0;
};

class qt_factory : public abstract_factory
{
    std::shared_ptr<base_drawer> create_ui() const override;
};

#endif // ABSTRACT_FACTORY_HPP
