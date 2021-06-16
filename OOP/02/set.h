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

template <typename T>
class set : public abstract_container
{
public:
    set();
    explicit set(const set<T> &s);
    set(set<T> &&s) noexcept;
    set(const T *arr, long size);
    set(const std::initializer_list<T> &elems);

    template <typename iter>
    set(iter begin, iter end);

    ~set() = default;

    virtual bool is_empty() const override;
    virtual void clear() override;

    operator bool() const;

    set<T> &append(const T &data);
    set<T> operator +(const T &data);
    set<T> &operator +=(const T &data);

    set<T> &subtract(const T &data);
    set<T> operator -(const T &data);
    set<T> &operator -=(const T &data);

    set<T> &sym_dif(const T &data);
    set<T> operator ^(const T &data);
    set<T> &operator ^=(const T &data);

    set<T> &log_and(const T &data);
    set<T> operator &(const T &data);
    set<T> &operator &=(const T &data);

    set<T> &log_or(const T &data);
    set<T> operator |(const T &data);
    set<T> &operator |=(const T &data);

    bool belong(const T &data) const;
    bool operator <(const T &data) const;
    bool operator <=(const T &data) const;

    set<T> &append(const set<T> &s);
    set<T> &append(const std::initializer_list<T> &elems);
    set<T> operator +(const set<T> &s);
    set<T> &operator +=(const set<T> &s);

    set<T> &subtract(const set<T> &s);
    set<T> &subtract(const std::initializer_list<T> &elems);
    set<T> operator -(const set<T> &s);
    set<T> &operator -=(const set<T> &s);

    set<T> &sym_dif(const set<T> &s);
    set<T> operator ^(const set<T> &s);
    set<T> &operator ^=(const set<T> &s);

    set<T> &log_and(const set<T> &s);
    set<T> operator &(const set<T> &s);
    set<T> &operator &=(const set<T> &s);

    set<T> &log_or(const set<T> &s);
    set<T> operator |(const set<T> &s);
    set<T> &operator |=(const set<T> &s);

    set<T> &operator =(const set<T> &s);
    set<T> &operator =(set<T> &&s) const;

    bool belong(const set<T> &s) const;
    bool operator <(const set<T> &s) const;
    bool operator <=(const set<T> &s) const;

    bool operator ==(const set<T> &s) const;
    bool operator !=(const set<T> &s) const;

    long get_size() const;

    set_iterator<T> begin();
    set_iterator<T> end();
    const_set_iterator<T> begin() const;
    const_set_iterator<T> end() const;
    const_set_iterator<T> cbegin() const;
    const_set_iterator<T> cend() const;

private:
    const_set_iterator<T> find(const T &data) const;

    std::shared_ptr<set_node<T>> head;
    std::shared_ptr<set_node<T>> tail;
    long size;
};

#include "set.hpp"

#endif // SET_H
