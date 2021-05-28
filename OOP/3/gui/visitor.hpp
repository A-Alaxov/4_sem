#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "drawer.hpp"

class model;
class camera;
class composite;

class visitor
{
public:
    visitor() = default;
    visitor(const std::shared_ptr<camera> &_camera, const std::shared_ptr<base_drawer> _drawer);
    ~visitor() =default;

    void visit_model(model &_model);
    void visit_camera(camera &_camera) {};
    void visit_composite(composite &_composite) {};

private:
    point get_projection(point &_point);
    std::shared_ptr<camera> _camera;
    std::shared_ptr<base_drawer> _drawer;
};

#endif // VISITOR_HPP
