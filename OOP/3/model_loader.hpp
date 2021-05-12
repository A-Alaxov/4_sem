#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include "model.hpp"
#include "builder.hpp"
#include "source_loader.hpp"

class base_model_loader
{
public:
    base_model_loader() = default;
    ~base_model_loader() = default;

    virtual std::shared_ptr<model> load_model(std::string name) = 0;

protected:
    std::shared_ptr<source_loader> src_loader;
};

class model_loader : public base_model_loader
{
public:
    model_loader() = default;
    model_loader(std::shared_ptr<source_loader> src_loader, std::shared_ptr<base_builder> builder);
    ~model_loader() = default;

    std::shared_ptr<model> load_model(std::string name) override;

private:
    std::shared_ptr<base_builder> builder;
};

#endif // LOADER_HPP
