#include "builder.hpp"
#include "errors.hpp"

bool model_builder::is_build()
{
    return _model != nullptr;
}

void model_builder::build()
{
    _model.reset();
    //_model = std::shared_ptr<model>(std::make_shared<model>());
    _model = std::make_shared<model>();
}

void model_builder::build_point(point pt)
{
    if (!is_build())
    {
        std::string message = "Error while building point";
        throw file_error(message);
    }
    _model->add_point(pt);
}

void model_builder::build_edge(edge ed)
{
    if (!is_build())
    {
        std::string message = "Error while building edge";
        throw file_error(message);
    }
    _model->add_edge(ed);
}

std::shared_ptr<model> model_builder::get()
{
    return _model;
}
