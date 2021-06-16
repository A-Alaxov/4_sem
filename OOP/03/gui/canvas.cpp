#include "canvas.hpp"

void qt_canvas::draw_line(const point &p1, const point &p2)
{
    scene->addLine(p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y());
}

void qt_canvas::clear()
{
    scene->clear();
}
