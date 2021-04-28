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
    set(const T * arr, long size);
    explicit set(const std::initializer_list<T> &elems);

    template <typename iter>
    set(iter begin, iter end);

    ~set() = default;

    virtual bool is_empty() const override;
    virtual void clear() override;

    operator bool() const;

    bool append(const T &data);
    void append(const set<T> &s);
    void append(std::initializer_list<T> elems);

    bool subtract(const T &data);
    void subtract(const set<T> &s);
    void subtract(std::initializer_list<T> elems);

    set<T> &add(const set<T> &s);
    set<T> &add(const T &data);

    set<T> operator +(const set<T> &s);
    set<T> operator +(const T &data);
    set<T> &operator +=(const set<T> &s);
    set<T> &operator +=(const T &data);

    set<T> &sub(const set<T> &s);
    set<T> &sub(const T &data);

    set<T> operator -(const set<T> &s);
    set<T> operator -(const T &data);
    set<T> &operator -=(const set<T> &s);
    set<T> &operator -=(const T &data);

    set<T> &sym_dif(const set<T> &s);
    set<T> &sym_dif(const T &data);

    set<T> operator ^(const set<T> &s);
    set<T> operator ^(const T &data);
    set<T> &operator ^=(const set<T> &s);
    set<T> &operator ^=(const T &data);

    set<T> &log_and(const set<T> &s);
    set<T> &log_and(const T &data);

    set<T> operator &(const set<T> &s);
    set<T> operator &(const T &data);
    set<T> &operator &=(const set<T> &s);
    set<T> &operator &=(const T &data);

    set<T> &log_or(const set<T> &s);
    set<T> &log_or(const T &data);

    set<T> operator |(const set<T> &s);
    set<T> operator |(const T &data);
    set<T> &operator |=(const set<T> &s);
    set<T> &operator |=(const T &data);

    set<T> &operator =(const set<T> &s);
    set<T> &operator =(set<T> &&s) const;

    bool operator ==(const set<T> &s) const;
    bool operator !=(const set<T> &s) const;

    long get_size() const;

    const_set_iterator<T> find(const T &data) const;

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
