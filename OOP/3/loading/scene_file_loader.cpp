#include "scene_file_loader.hpp"
#include "camera_file_loader.hpp"
#include "model_file_loader.hpp"
#include <fstream>

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

std::shared_ptr<scene> scene_file_loader::load()
{
    builder->build();

    if (!is_open())
    {
        std::string message = "Error in reading edges from file";
        throw file_error(message);
    }

    load_models();
    load_cameras();

    return std::shared_ptr<scene>(builder->get());
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
