#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <QGraphicsScene>
#include "point.hpp"

class base_drawer
{
public:
    base_drawer() = default;
    virtual ~base_drawer() = default;

    virtual void draw_line(const point &point1, const point &point2) = 0;
    virtual void clear_scene() = 0;
};

class qt_drawer : public base_drawer
{
public:
    qt_drawer() : scene(nullptr) {};
    qt_drawer(QGraphicsScene *scene) : scene(scene) {};
    qt_drawer(const qt_drawer &drawer);
    ~qt_drawer() = default;

    void draw_line(const point &point1, const point &point2) override;
    void clear_scene() override;

private:
    QGraphicsScene *scene;
};

#endif // DRAWER_HPP
