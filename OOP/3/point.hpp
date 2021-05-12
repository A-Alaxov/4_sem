#ifndef POINT_HPP
#define POINT_HPP


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

    void move(point &move);
    void scale(point &scale);
    void rotate(point &rotate);

private:
    void rotate_in_flat(double &coord_1, double &coord_2, double &angle);
    double x;
    double y;
    double z;
};

#endif // POINT_HPP
