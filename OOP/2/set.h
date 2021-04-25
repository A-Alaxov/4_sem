#ifndef SET_H
#define SET_H

#include <initializer_list>
#include <memory>
#include <chrono>

#include "abstract_container.h"
#include "set_expectations.h"
#include "set_node.h"
#include "const_set_iterator.h"
#include "set_iterator.h"

//namespace container
//{
template <typename T>
class set : public abstract_container
{
public:
    set();
    explicit set(const set<T> &s);
    set(set<T> &&s) noexcept;
    explicit set(const std::initializer_list<T> &elems);

    ~set() = default;

    template <typename iter>
    set(iter begin, iter end);

    virtual bool is_empty() const override;
    virtual void clear() override;

    bool append(const T &data);
    bool subtract(const T &data);

    long get_size() const;

    std::shared_ptr<set_node<T>> find(const T &data) const;

    set_iterator<T> begin();
    set_iterator<T> end();
    const_set_iterator<T> begin() const;
    const_set_iterator<T> end() const;
    const_set_iterator<T> cbegin() const;
    const_set_iterator<T> cend() const;

private:
    std::shared_ptr<set_node<T>> head;
    std::shared_ptr<set_node<T>> tail;
    long size;
};
//}

#include "set.hpp"

#endif // SET_H
