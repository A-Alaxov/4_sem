#include "composite.hpp"

bool composite::add(std::shared_ptr<object> obj)
{
    objects.push_back(obj);
    return true;
}

void composite::accept(std::shared_ptr<visitor> _visitor)
{
    for (auto obj : objects)
        obj->accept(_visitor);
}

void composite::reform(point &move, point &scale, point &rotate)
{
    for (auto obj : objects)
        obj->reform(move, scale, rotate);
}
