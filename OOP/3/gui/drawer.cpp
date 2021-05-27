#include "drawer.hpp"

void qt_drawer::draw_line(const point &p1, const point &p2)
{
    canvas->draw_line(p1, p2);
}

void qt_drawer::set_canvas(std::shared_ptr<base_canvas> canvas)
{
    this->canvas = canvas;
}

void qt_drawer::clear_scene()
{
    canvas->clear();
}
