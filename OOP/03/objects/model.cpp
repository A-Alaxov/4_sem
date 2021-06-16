#include "model.hpp"

model::model()
    :_details(std::make_shared<details>())
{
}

model::model(const std::shared_ptr<details> &_details)
    :_details(_details)
{
}

void model::accept(std::shared_ptr<visitor> _visitor)
{
    _visitor->visit_model(*this);
}

void model::reform(std::shared_ptr<Matrix<double>> reform_mtr)
{
    _details->reform(reform_mtr);
}
