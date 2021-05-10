#ifndef MODEL_HPP
#define MODEL_HPP

#include "object.hpp"
#include "details.hpp"

class model : public visible_object
{
public:
    model();
    ~model();

    void accept() override;
    bool is_composite() override { return false; }
    void reform() override;

private:
    std::shared_ptr<details> _details;
};

#endif // MODEL_HPP
