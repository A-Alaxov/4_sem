#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include "model.hpp"
#include "builder.hpp"
#include "source_loader.hpp"

class load_general_secretary
{
public:
    load_general_secretary() = default;
    ~load_general_secretary() = default;

    virtual std::shared_ptr<object> load(std::string name) = 0;

protected:
    std::shared_ptr<source_loader> src_loader;
};

class model_secretary : public load_general_secretary
{
public:
    model_secretary();
    ~model_secretary() = default;

    std::shared_ptr<object> load(std::string name) override;
};

class camera_secretary : public load_general_secretary
{
public:
    camera_secretary();
    ~camera_secretary() = default;

    std::shared_ptr<object> load(std::string name) override;
};

class scene_secretary : public load_general_secretary
{
public:
    scene_secretary();
    ~scene_secretary() = default;

    std::shared_ptr<object> load(std::string name) override;
};

#endif // LOADER_HPP
