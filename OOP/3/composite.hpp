#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <vector>
#include "object.hpp"

class composite : public object
{
public:
    composite() = default;
    ~composite() = default;

    bool add(std::shared_ptr<object> obj) override;
    bool remove() override { return false; }
    std::vector<std::shared_ptr<object>>::iterator begin() override { return std::vector<std::shared_ptr<object>>::iterator(); }
    std::vector<std::shared_ptr<object>>::iterator end() override { return std::vector<std::shared_ptr<object>>::iterator(); }

    void accept(std::shared_ptr<visitor> _visitor) override;
    bool is_composite() override { return true; };
    bool is_visible() override { return false; };
    void reform() override {};

private:
    std::vector<std::shared_ptr<object>> objects;
};

#endif // COMPOSITE_HPP
