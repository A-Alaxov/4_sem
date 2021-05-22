#ifndef OBJECT_CAMERA_HPP
#define OBJECT_CAMERA_HPP

#include "object.hpp"
#include "camera_details.hpp"

class camera : public invisible_object
{
public:
    camera();

    const point &get_position() const;
    const point &get_angles() const;
    void set_position(const point &position);
    void rotate(const std::shared_ptr<Matrix<double>> reform_mtr);

    void reform(const std::shared_ptr<Matrix<double>> reform_mtr) override;
    bool is_composite() override { return false; }
    void accept(std::shared_ptr<visitor> _visitor) override;

private:
    point position;
    point angles;
};

#endif
