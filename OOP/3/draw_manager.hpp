#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include <memory>
#include "visitor.hpp"
#include "drawer.hpp"
#include "scene.hpp"

class draw_manager : public visitor
{
public:
    void set_drawer(std::shared_ptr<base_drawer> drawer);
    //void set_camera(std::shared_ptr<camera> _camera);

    void visit_model(model &_model) override;
    //void visit_camera(camera &_camera) override;
    void visit_composite(composite &_composite) override {};

private:
    point get_projection(point &_point);
    std::shared_ptr<base_drawer> drawer;
    //std::shared_ptr<camera> _camera;
};

#endif // DRAW_MANAGER_HPP
