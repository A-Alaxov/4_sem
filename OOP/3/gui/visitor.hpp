#ifndef VISITOR_HPP
#define VISITOR_HPP

class model;
class camera;
class composite;
class scene;

class visitor
{
public:
    visitor() = default;
    virtual ~visitor() =default;

    virtual void visit_model(model &_model) = 0;
    virtual void visit_camera(camera &_camera) = 0;
    virtual void visit_composite(composite &_composite) = 0;
    virtual void visit_scene(scene &_scene) = 0;
};

#endif // VISITOR_HPP
