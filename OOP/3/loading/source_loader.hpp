#ifndef SOURCE_LOADER_HPP
#define SOURCE_LOADER_HPP

#include "point.hpp"
#include "edge.hpp"
#include "builder.hpp"

#include <vector>
#include <string>
#include <fstream>
#include "object.hpp"
#include "base_loader.hpp"

class model_file_loader : public base_model_loader
{
public:
    model_file_loader();
    explicit model_file_loader(std::shared_ptr<std::ifstream> &file) : file(file) {}
    ~model_file_loader();

    void open(std::string &name) override;
    void close() override;
    bool is_open() override;
    std::shared_ptr<object> load() override;

private:
    std::vector<point> read_points();
    std::vector<edge> read_edges();
    std::shared_ptr<std::ifstream> file;
    std::shared_ptr<model_builder> builder;
};

class camera_file_loader : public base_camera_loader
{
public:
    camera_file_loader();
    ~camera_file_loader();
    explicit camera_file_loader(std::shared_ptr<std::ifstream> &file) : file(file) {}
    void open(std::string &name) override;
    std::shared_ptr<object> load() override;
    void close() override;
    bool is_open() override;

private:
    std::shared_ptr<std::ifstream> file;
    std::shared_ptr<camera_builder> builder;
};

class scene_file_loader : public base_scene_loader
{
public:
    scene_file_loader();
    ~scene_file_loader();
    explicit scene_file_loader(std::shared_ptr<std::ifstream> &file);
    void open(std::string &name) override;
    std::shared_ptr<object> load() override;
    void close() override;
    bool is_open() override;

private:
    std::shared_ptr<std::ifstream> file;
    std::shared_ptr<scene_builder> builder;

    void load_models();
    void load_cameras();
};

#endif // SOURCE_LOADER_HPP
