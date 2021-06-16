#ifndef OBJECT_CAMERA_HPP
#define OBJECT_CAMERA_HPP

#include "object.hpp"
#include "visitor.hpp"
#include "commands.hpp"

class camera : public invisible_object
{
    friend class visitor;
    friend class reform_camera;
public:
    camera();
    explicit camera(const point &pos, const point &angs);
/*
    const point &get_position() const;
    const point &get_angles() const;
    void set_position(const point &position);
    void set_angles(const point &angles);
    void rotate(const std::shared_ptr<Matrix<double>> reform_mtr);
*/
    void reform(const std::shared_ptr<Matrix<double>> reform_mtr) override;
    bool is_composite() override { return false; }
    void accept(std::shared_ptr<visitor> _visitor) override;

private:
    point position;
    point angles;

    const point &get_position() const;
    const point &get_angles() const;
    void set_position(const point &position);
    void set_angles(const point &angles);
    void rotate(const std::shared_ptr<Matrix<double>> reform_mtr);
};

#endif
