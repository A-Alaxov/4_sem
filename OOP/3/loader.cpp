#include "loader.hpp"
#include "errors.hpp"
#include <fstream>

std::shared_ptr<model> file_loader::load_model(std::string name)
{
    std::fstream f;
    f.open(name);

    if (!f)
    {
        std::string message = "Error while open file.";
        throw file_error(message);
    }

    builder->build();

    long points_count;
    f >> points_count;

    for (long i = 0; i < points_count; i++)
    {
        double x, y, z;
        f >> x >> y >> z;
        builder->build_point(x, y, z);
    }

    long links_count;
    f >> links_count;

    for (long i = 0; i < links_count; i++)
    {
        long point1, point2;
        f >> point1 >> point2;
        builder->build_edge(point1, point2);
    }

    try
    {
        f.close();
    } catch (std::ifstream::failure &error)
    {
        error.what();
    }

    return builder->get();
}
