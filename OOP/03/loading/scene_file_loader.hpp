#ifndef SCENE_FILE_LOADER_HPP
#define SCENE_FILE_LOADER_HPP

#include "base_loader.hpp"
#include "builder.hpp"

class scene_file_loader : public base_scene_loader
{
public:
    scene_file_loader();
    ~scene_file_loader();
    explicit scene_file_loader(std::shared_ptr<std::ifstream> &file);
    void open(std::string &name) override;
    std::shared_ptr<scene> load() override;
    void close() override;
    bool is_open() override;

private:
    std::shared_ptr<std::ifstream> file;
    std::shared_ptr<scene_builder> builder;

    void load_models();
    void load_cameras();
};

#endif // SCENE_FILE_LOADER_HPP
