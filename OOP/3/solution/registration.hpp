#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <map>

#include "loaders.hpp"
#include "drawer_factory.hpp"
#include "solution.hpp"

class base_registration_maker
{
public:
    base_registration_maker() = default;
    virtual ~base_registration_maker() = default;
    virtual void make_registration(solution &_solution) = 0;
};

class registration_maker : public base_registration_maker
{
public:
    registration_maker() = default;
    ~registration_maker() = default;
    void make_registration(solution &_solution) override;
};

#endif // REGISTRATION_H
