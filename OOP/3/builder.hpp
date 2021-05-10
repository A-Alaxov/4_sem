#ifndef BASE_BUILDER_HPP
#define BASE_BUILDER_HPP

#include "model.hpp"

class base_builder
{
public:
    base_builder();
    ~base_builder();

    virtual bool is_build() = 0;
    virtual void build() = 0;
    virtual void build_point(double x, double y, double z) = 0;
    virtual void build_edge(long point1, long point2) = 0;

    virtual std::shared_ptr<model> get() = 0;
};

class model_builder : public base_builder
{
public:
    model_builder();
    ~model_builder();

    bool is_build() override;
    void build() override;
    void build_point(double x, double y, double z) override;
    void build_edge(long point1, long point2) override;

    std::shared_ptr<model> get() override;

private:
    std::shared_ptr<model> model;
};

#endif // BASE_BUILDER_HPP
