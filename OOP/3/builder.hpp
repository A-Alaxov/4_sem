#ifndef BASE_BUILDER_HPP
#define BASE_BUILDER_HPP

#include "model.hpp"

class base_builder
{
public:
    base_builder() = default;
    ~base_builder() = default;

    virtual bool is_build() = 0;
    virtual void build() = 0;
    virtual void build_point(point pt) = 0;
    virtual void build_edge(edge ed) = 0;

    virtual std::shared_ptr<model> get() = 0;
};

class model_builder : public base_builder
{
public:
    model_builder() = default;
    ~model_builder() = default;

    bool is_build() override;
    void build() override;
    void build_point(point pt) override;
    void build_edge(edge ed) override;

    std::shared_ptr<model> get() override;

private:
    std::shared_ptr<model> _model;
};

#endif // BASE_BUILDER_HPP
