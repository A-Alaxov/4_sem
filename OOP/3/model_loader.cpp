#include "model_loader.hpp"

model_loader::model_loader(std::shared_ptr<source_loader> src_loader, std::shared_ptr<base_builder> builder)
{
    this->src_loader = src_loader;
    this->builder = builder;
}

std::shared_ptr<model> model_loader::load_model(std::string name)
{
    src_loader->open(name);

    builder->build();

    std::vector<point> points = src_loader->read_points();

    for (auto point : points)
    {
        builder->build_point(point);
    }

    std::vector<edge> edges = src_loader->read_edges();

    for (auto edge : edges)
    {
        builder->build_edge(edge);
    }

    src_loader->close();

    return builder->get();
}
