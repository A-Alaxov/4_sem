#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <QGraphicsScene>
#include "point.hpp"

#include "canvas.hpp"

class base_drawer
{
public:
    base_drawer() = default;
    virtual ~base_drawer() = default;

    virtual void set_canvas(std::shared_ptr<base_canvas> canvas) = 0;
    virtual void draw_line(const point &point1, const point &point2) = 0;
    virtual void clear_scene() = 0;

protected:
    std::shared_ptr<base_canvas> canvas;
};

class qt_drawer : public base_drawer
{
public:
    qt_drawer() = default;

    void set_canvas(std::shared_ptr<base_canvas> canvas) override;
    void draw_line(const point &point1, const point &point2) override;
    void clear_scene() override;
};

#endif // DRAWER_HPP
