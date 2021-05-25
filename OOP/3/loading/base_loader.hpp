#ifndef BASE_LOADER_HPP
#define BASE_LOADER_HPP

#include <string>
#include <memory>

class object;

class source_loader
{
public:
    source_loader() = default;
    ~source_loader() = default;

    virtual void open(std::string &name) = 0;
    virtual void close() = 0;
    virtual bool is_open() = 0;
    virtual std::shared_ptr<object> load() = 0;
};

class base_model_loader : public source_loader
{
public:
    base_model_loader() = default;
    ~base_model_loader() = default;

    virtual void open(std::string &name) = 0;
    virtual void close() = 0;
    virtual bool is_open() = 0;
    virtual std::shared_ptr<object> load() = 0;
};

class base_camera_loader : public source_loader
{
public:
    base_camera_loader() = default;
    ~base_camera_loader() = default;

    virtual void open(std::string &name) = 0;
    virtual void close() = 0;
    virtual bool is_open() = 0;
    virtual std::shared_ptr<object> load() = 0;
};

class base_scene_loader : public source_loader
{
public:
    base_scene_loader() = default;
    ~base_scene_loader() = default;

    virtual void open(std::string &name) = 0;
    virtual void close() = 0;
    virtual bool is_open() = 0;
    virtual std::shared_ptr<object> load() = 0;
};

#endif // BASE_LOADER_HPP
