#include "composite.hpp"

bool composite::add(std::shared_ptr<object> obj)
{
    objects.push_back(obj);
    return true;
}

bool composite::remove(long index)
{
    objects.erase(objects.begin() + index);
    return true;
}

void composite::accept(std::shared_ptr<visitor> _visitor)
{
    for (auto obj : objects)
        obj->accept(_visitor);
}

void composite::reform(std::shared_ptr<Matrix<double>> reform_mtr)
{
    for (auto obj : objects)
        obj->reform(reform_mtr);
}
