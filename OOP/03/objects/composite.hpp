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
    bool remove(long index) override;
    std::vector<std::shared_ptr<object>>::iterator begin() override { return objects.begin(); }
    std::vector<std::shared_ptr<object>>::iterator end() override { return objects.end(); }
    std::vector<std::shared_ptr<object>>::const_iterator cbegin() const override { return objects.begin(); }
    std::vector<std::shared_ptr<object>>::const_iterator cend() const override { return objects.end(); }

    void accept(std::shared_ptr<visitor> _visitor) override;
    bool is_composite() override { return true; };
    bool is_visible() override { return false; };
    void reform(std::shared_ptr<Matrix<double>> reform_mtr) override;

    std::vector<std::shared_ptr<object>> &get_objects() { return objects; };

private:
    std::vector<std::shared_ptr<object>> objects;
};

#endif // COMPOSITE_HPP
