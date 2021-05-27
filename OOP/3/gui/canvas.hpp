#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "QGraphicsScene"
#include "point.hpp"

class base_canvas
{
public:
    virtual void draw_line(const point &p1, const point &p2) = 0;
    virtual void clear() = 0;
};

class qt_canvas : public base_canvas
{
public:
    //explicit qt_canvas(std::shared_ptr<QGraphicsScene> canvas) : scene(canvas) {}
    explicit qt_canvas(QGraphicsScene *canvas) : scene(canvas) {}
    void draw_line(const point &p1, const point &p2) override;
    void clear() override;

private:
    //std::shared_ptr<QGraphicsScene> scene;
    QGraphicsScene *scene;
};

#endif // CANVAS_HPP
