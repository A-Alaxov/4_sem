#ifndef CREATOR_HPP
#define CREATOR_HPP

#include "controller.hpp"

class creator
{
public:
    virtual ~creator() = default;
    std::shared_ptr<base_controller> get_product()
    {
        if (!product)
        {
            product = create_product();
        }
        return product;
    }

protected:
    virtual std::shared_ptr<base_controller> create_product() = 0;

private:
    std::shared_ptr<base_controller> product;
};

//creator::~creator() = default;

template <typename Tcontroller>
class con_creator : public creator
{
protected:
    std::shared_ptr<base_controller> create_product() override
    {
        return std::shared_ptr<base_controller>(new Tcontroller());
    }
};
/*
std::shared_ptr<base_controller> creator::get_product()
{
    if (!product)
    {
        product = create_product();
    }
    return product;
}
*/
#endif // CREATOR_HPP
