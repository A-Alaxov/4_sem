#ifndef POINT_HPP
#define POINT_HPP


class point
{
public:
    point();
    ~point();

    double get_x();
    double get_y();
    double get_z();

    void set_x(double x);
    void set_y(double y);
    void set_z(double z);

    void move();
    void scale();
    void rotate();

private:
    double x;
    double y;
    double z;
};

#endif // POINT_HPP
