#ifndef CAMERA_DETAILS_HPP
#define CAMERA_DETAILS_HPP

#include "point.hpp"

class camera_details
{
public:
public:
    camera_details() = default;
    ~camera_details() = default;

    void reform(std::shared_ptr<Matrix<double>> reform_mtr);

    const point &get_position() { return position; }
    const point &get_angles() { return angles; }

    void set_position(const point &position);
    void set_angles(const point &angles);

private:
    point position;
    point angles;
};

#endif // CAMERA_DETAILS_HPP
