#include "camera_details.hpp"

void camera_details::set_position(const point &position)
{
    this->position = position;
}

void camera_details::set_angles(const point &angles)
{
    this->angles = angles;
}

void camera_details::reform(std::shared_ptr<Matrix<double>> reform_mtr)
{
    position.reform(reform_mtr);
    angles.reform(reform_mtr);
}
