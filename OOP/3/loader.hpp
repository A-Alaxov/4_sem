#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include "model.hpp"
#include "builder.hpp"

class base_loader
{
public:
    base_loader() = default;
    ~base_loader() = default;

    virtual std::shared_ptr<model> load_model(std::string name) = 0;
};

class file_loader : public base_loader
{
public:
    file_loader() = default;
    ~file_loader() = default;

    std::shared_ptr<model> load_model(std::string name) override;

private:
    std::shared_ptr<base_builder> builder;
};

#endif // LOADER_HPP
