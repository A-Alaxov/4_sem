#include "draw_manager.hpp"
#include "errors.hpp"
#include <math.h>

void draw_manager::set_drawer(std::shared_ptr<base_drawer> drawer)
{
    this->drawer = drawer;
}

void draw_manager::visit_model(model &_model)
{
    if (!drawer)
    {
        std::string message = "Error while drawing model";
        throw file_error(message);
    }
    //if (!_camera)
    //{
    //    throw CameraError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    //}

    auto details = _model.get_details();
    auto points = details->get_points();
    auto edges = details->get_edges();

    for (auto &edge : edges)
    {
        //point p1 = get_projection(points[edge.get_first()]);
        //point p2 = get_projection(points[edge.get_second()]);
        drawer->draw_line(get_projection(points[edge.get_first()]),
                          get_projection(points[edge.get_second()]));
        //drawer->draw_line(p1, p2);
    }
}

point draw_manager::get_projection(point &_point)
{
    point projection(_point);
    projection.set_x(_point.get_y() - _point.get_x() * sqrt(3) / 2);
    projection.set_y(_point.get_z() / 2 - _point.get_z());

    return projection;
}
