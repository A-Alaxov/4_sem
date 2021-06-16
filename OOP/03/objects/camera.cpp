#include "camera.hpp"

camera::camera()
{
    position = point(0, 0, 0);
    angles = point(0, 0, 0);
}

camera::camera(const point &pos, const point &angs)
    :position(pos), angles(angs)
{
}

const point &camera::get_position() const
{
    return position;
}

const point &camera::get_angles() const
{
    return angles;
}

void camera::set_position(const point &position)
{
    this->position = position;
}

void camera::set_angles(const point &angles)
{
    this->angles = angles;
}

void camera::reform(const std::shared_ptr<Matrix<double>> reform_mtr)
{
    position.reform(reform_mtr);
}

void camera::accept(std::shared_ptr<visitor> _visitor)
{
    _visitor->visit_camera(*this);
}

void camera::rotate(const std::shared_ptr<Matrix<double>> reform_mtr)
{
    angles.reform(reform_mtr);
}
