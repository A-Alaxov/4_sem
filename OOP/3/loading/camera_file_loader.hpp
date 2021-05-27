#ifndef CAMERA_FILE_LOADER_HPP
#define CAMERA_FILE_LOADER_HPP

#include "base_loader.hpp"
#include "builder.hpp"

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

#endif // CAMERA_FILE_LOADER_HPP
