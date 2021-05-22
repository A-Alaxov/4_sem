#ifndef POINT_HPP
#define POINT_HPP

#include <memory>
#include "matrix.hpp"

class point
{
public:
    point();
    point(const double x, const double y, const double z);
    ~point() = default;

    double get_x() const { return x; };
    void set_x(double x) { this->x = x; };

    double get_y() const { return y; };
    void set_y(double y) { this->y = y; };

    double get_z() const { return z; };
    void set_z(double z) { this->z = z; };

    void reform(const std::shared_ptr<Matrix<double>> mtr);
    point deg_to_rad() const;

private:
    double x;
    double y;
    double z;
};

#endif // POINT_HPP
