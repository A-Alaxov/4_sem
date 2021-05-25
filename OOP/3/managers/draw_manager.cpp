#include "draw_manager.hpp"
#include "errors.hpp"
#include "transform_matrix.hpp"
#include <math.h>

std::shared_ptr<draw_manager> draw_manager_creator::get_manager()
{
    if (_manager == nullptr)
        create_manager();

    return _manager;
}

void draw_manager_creator::create_manager()
{
    static std::shared_ptr<draw_manager> _manager(new draw_manager());
    this->_manager = _manager;
}

void draw_manager::set_drawer(std::shared_ptr<base_drawer> drawer)
{
    this->drawer = drawer;
}

void draw_manager::set_camera(std::shared_ptr<camera> _camera)
{
    this->_camera = _camera;
}

void draw_manager::visit_model(model &_model)
{
    if (!drawer)
    {
        std::string message = "Error while drawing model";
        throw file_error(message);
    }
    if (!_camera)
    {
        std::string message = "Error while drawing model";
        throw file_error(message);
    }

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
    point move(-_camera->get_position().get_x(), -_camera->get_position().get_y(), 0);
    //std::shared_ptr<Matrix<double>> reform_mtr(std::make_shared<MoveMatrix>(move));
    std::shared_ptr<Matrix<double>> reform_mtr(std::make_shared<MoveMatrix>(_camera->get_position()));

    projection.reform(reform_mtr);

    point angles = _camera->get_angles().deg_to_rad();
    reform_mtr = std::make_shared<RotateOxMatrix>(-angles.get_x());
    projection.reform(reform_mtr);

    reform_mtr = std::make_shared<RotateOyMatrix>(-angles.get_y());
    projection.reform(reform_mtr);

    reform_mtr = std::make_shared<RotateOzMatrix>(-angles.get_z());
    projection.reform(reform_mtr);

    return projection;
}
