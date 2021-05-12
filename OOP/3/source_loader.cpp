#include "source_loader.hpp"
#include "errors.hpp"

file_loader::~file_loader()
{
    close();
}

void file_loader::open(std::string name)
{
    if (is_open())
        close();

    file.open(name);
    if (!file)
    {
        std::string message = "Error while open file";
        throw file_error(message);
    }
}

void file_loader::close()
{
    try
    {
        file.close();
    } catch (std::ifstream::failure &error)
    {
        error.what();
    }
}

bool file_loader::is_open()
{
    return file.is_open();
}

std::vector<point> file_loader::read_points()
{
    if (!is_open())
    {
        std::string message = "Error in reading poits from file";
        throw file_error(message);
    }

    std::vector<point> points;
    long points_count;
    file >> points_count;

    for (long i = 0; i < points_count; i++)
    {
        double x, y, z;
        file >> x >> y >> z;
        points.push_back(point(x, y, z));
    }

    return points;
}

std::vector<edge> file_loader::read_edges()
{
    if (!is_open())
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }

    std::vector<edge> edges;
    long edges_count;
    file >> edges_count;

    for (long i = 0; i < edges_count; i++)
    {
        long point1, point2;
        file >> point1 >> point2;
        edges.push_back(edge(point1, point2));
    }

    return edges;
}
