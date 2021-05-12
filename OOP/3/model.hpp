#ifndef MODEL_HPP
#define MODEL_HPP

#include "object.hpp"
#include "details.hpp"

class model : public visible_object
{
public:
    model();
    model(const model &_model);
    model(model &&_model) noexcept;
    ~model() = default;

    void accept(std::shared_ptr<visitor> _visitor) override;
    bool is_composite() override { return false; }
    void reform(point &move, point &scale, point &rotate) override;

    void add_point(point pt);
    void add_edge(edge ed);
    const std::shared_ptr<details> get_details() const { return _details; };

    model &operator=(const model &_model);
    model &operator=(model &&_model) noexcept;

private:
    std::shared_ptr<details> _details;
};

#endif // MODEL_HPP
