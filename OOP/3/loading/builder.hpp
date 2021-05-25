#ifndef BASE_BUILDER_HPP
#define BASE_BUILDER_HPP

#include "model.hpp"

class model_builder
{
public:
    model_builder() = default;
    ~model_builder() = default;

    bool is_build();
    void build();
    void build_points(std::vector<point> pt);
    void build_edges(std::vector<edge> ed);

    std::shared_ptr<object> get();

private:
    std::shared_ptr<details> _details;
};

class scene_builder
{
public:
    scene_builder() = default;
    ~scene_builder() = default;

    bool is_build();
    void build();
    void build_model(const std::shared_ptr<object> &_model);
    void build_camera(const std::shared_ptr<object> &_camera);

    std::shared_ptr<object> get();

private:
    std::shared_ptr<scene> _scene;
};

class camera_builder
{
public:
    camera_builder() = default;
    ~camera_builder() = default;

    bool is_build();
    void build();
    void build_pos(double x, double y, double z);
    void build_angles(double ox, double oy, double oz);

    std::shared_ptr<object> get();

private:
    std::shared_ptr<camera> _camera;
};

#endif // BASE_BUILDER_HPP
