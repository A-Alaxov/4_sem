#include "source_loader.hpp"
#include "errors.hpp"

model_file_loader::model_file_loader()
{
    file = std::shared_ptr<std::ifstream>(new std::ifstream);
    builder = std::shared_ptr<model_builder>(new model_builder);
}

model_file_loader::~model_file_loader()
{
    close();
}

void model_file_loader::open(std::string &name)
{
    if (is_open())
        close();

    file->open(name);
    if (!file)
    {
        std::string message = "Error while open file";
        throw file_error(message);
    }
}

void model_file_loader::close()
{
    try
    {
        file->close();
    } catch (std::ifstream::failure &error)
    {
        error.what();
    }
}

bool model_file_loader::is_open()
{
    return file->is_open();
}

std::shared_ptr<object> model_file_loader::load()
{
    builder->build();

    std::vector<point> points = read_points();
    builder->build_points(points);

    std::vector<edge> edges = read_edges();
    builder->build_edges(edges);

    return std::dynamic_pointer_cast<object>(builder->get());
}

std::vector<point> model_file_loader::read_points()
{
    if (!is_open())
    {
        std::string message = "Error in reading poits from file";
        throw file_error(message);
    }

    std::vector<point> points;
    long points_count;
    *file >> points_count;

    for (long i = 0; i < points_count; i++)
    {
        double x, y, z;
        *file >> x >> y >> z;
        points.push_back(point(x, y, z));
    }

    return points;
}

std::vector<edge> model_file_loader::read_edges()
{
    if (!is_open())
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }

    std::vector<edge> edges;
    long edges_count;
    *file >> edges_count;

    for (long i = 0; i < edges_count; i++)
    {
        long point1, point2;
        *file >> point1 >> point2;
        edges.push_back(edge(point1, point2));
    }

    return edges;
}

camera_file_loader::camera_file_loader()
{
    file = std::shared_ptr<std::ifstream>(new std::ifstream);
    builder = std::shared_ptr<camera_builder>(new camera_builder);
}

camera_file_loader::~camera_file_loader()
{
    close();
}

void camera_file_loader::open(std::string &name)
{
    file->open(name);

    if (!is_open())
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }
}

std::shared_ptr<object> camera_file_loader::load()
{
    builder->build();

    if (!is_open())
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }

    double x, y, z;
    if (!(*file >> x >> y >> z))
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }
    builder->build_pos(x, y, z);

    if (!(*file >> x >> y >> z))
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }
    builder->build_angles(x, y, z);

    return std::dynamic_pointer_cast<object>(builder->get());
}

void camera_file_loader::close()
{
    file->close();
}

bool camera_file_loader::is_open()
{
    return file->is_open();
}

scene_file_loader::scene_file_loader()
{
    file = std::shared_ptr<std::ifstream>(new std::ifstream);
    builder = std::shared_ptr<scene_builder>(new scene_builder);
}

scene_file_loader::~scene_file_loader()
{
    close();
}

void scene_file_loader::open(std::string &name)
{
    file->open(name);

    if (!is_open())
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }
}

std::shared_ptr<object> scene_file_loader::load()
{
    builder->build();

    if (!is_open())
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }

    load_models();
    load_cameras();

    return std::dynamic_pointer_cast<object>(builder->get());
}

void scene_file_loader::close()
{
    file->close();
}

void scene_file_loader::load_models()
{
    size_t models_count;
    if (!(*file >> models_count))
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }
    for (size_t i = 0; i < models_count; i++)
    {
        builder->build_model(model_file_loader(file).load());
    }

}

void scene_file_loader::load_cameras()
{
    size_t cameras_count;
    if (!(*file >> cameras_count))
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }
    for (size_t i = 0; i < cameras_count; i++)
        builder->build_camera(camera_file_loader(file).load());
}

bool scene_file_loader::is_open()
{
    return file->is_open();
}
