#include "model.hpp"

model::model()
    :_details(std::make_shared<details>())
{
}

model::model(const model &_model)
    :visible_object(), _details(_model._details)
{
}

model::model(model &&_model) noexcept
    :_details(_model._details)
{
}

void model::add_point(point pt)
{
    _details->add_point(pt);
}

void model::add_edge(edge ed)
{
    _details->add_edge(ed);
}

void model::accept(std::shared_ptr<visitor> _visitor)
{
    _visitor->visit_model(*this);
}

model &model::operator=(const model &_model)
{
    if (this != &_model)
    {
        _details = _model._details;
    }

    return *this;
}

model &model::operator=(model &&_model) noexcept
{
    if (this != &_model)
    {
        _details = _model._details;
    }

    return *this;
}
