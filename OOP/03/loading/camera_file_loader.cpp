#include "camera_file_loader.hpp"
#include <fstream>

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
