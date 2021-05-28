#ifndef MODEL_HPP
#define MODEL_HPP

#include "object.hpp"
#include "details.hpp"
#include "visitor.hpp"

class model : public visible_object
{
    friend class visitor;
public:
    model();
    explicit model(const std::shared_ptr<details> &_details);

    void accept(std::shared_ptr<visitor> _visitor) override;
    bool is_composite() override { return false; }
    void reform(std::shared_ptr<Matrix<double>> reform_mtr) override;

private:
    std::shared_ptr<details> get_details() { return _details; }
    std::shared_ptr<details> _details;
};

#endif // MODEL_HPP
