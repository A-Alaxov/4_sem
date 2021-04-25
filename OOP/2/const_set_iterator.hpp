#ifndef CONST_SET_ITERATOR_HPP
#define CONST_SET_ITERATOR_HPP

#include <chrono>

#include "set_expectations.h"
//#include "const_set_iterator.h"

//namespace container
//{
template <typename T>
const_set_iterator<T>::const_set_iterator()
    :cur(std::weak_ptr<set_node<T>>())
{
}

template <typename T>
const_set_iterator<T>::const_set_iterator(const std::shared_ptr<set_node<T>> &node)
    :cur(node)
{
}

template <typename T>
const_set_iterator<T>::const_set_iterator(const const_set_iterator<T> &iterator)
    :cur(iterator.cur.lock())
{
}

template <typename T>
void const_set_iterator<T>::next()
{
    if (!cur.expired())
    {
        cur = cur.lock()->get_next();
    }
}

template <typename T>
void const_set_iterator<T>::prev()
{
    if (!cur.expired())
    {
        cur = cur.lock()->get_prev();
    }
}

template <typename T>
const_set_iterator<T>::operator bool()
{
    return cur.expired();
}

template <typename T>
const T &const_set_iterator<T>::operator *() const
{
    if (cur.expired())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw set_iterator_exception(ctime(&timenow), __FILE__, typeid(const_set_iterator).name(), __FUNCTION__);
    }

    return cur.lock()->get_data();
}

template <typename T>
const T &const_set_iterator<T>::operator ->() const
{
    if (cur.expired())
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw set_iterator_exception(ctime(&timenow), __FILE__, typeid(const_set_iterator).name(), __FUNCTION__);
    }

    return cur.lock().get_data_ptr();
}

template <typename T>
const_set_iterator<T> &const_set_iterator<T>::operator =(const const_set_iterator<T> &iterator)
{
    cur = iterator.cur;
    return *this;
}

template <typename T>
const_set_iterator<T> &const_set_iterator<T>::operator ++()
{
    next();
    return *this;
}

template <typename T>
const_set_iterator<T> const_set_iterator<T>::operator ++(int)
{
    auto temp = *this;
    next();
    return temp;
}

template <typename T>
const_set_iterator<T> &const_set_iterator<T>::operator --()
{
    prev();
    return *this;
}

template <typename T>
const_set_iterator<T> const_set_iterator<T>::operator --(int)
{
    auto temp = *this;
    prev();
    return temp;
}

template <typename T>
const_set_iterator<T> &const_set_iterator<T>::operator +=(long shift)
{
    for (int i = 0; i < shift; i++)
    {
        next();
    }
    return *this;
}

template <typename T>
const_set_iterator<T> const_set_iterator<T>::operator +(long shift) const
{
    auto it(*this);
    it += shift;
    return it;
}

template <typename T>
const_set_iterator<T> &const_set_iterator<T>::operator -=(long shift)
{
    for (int i = 0; i < shift; i++)
    {
        prev();
    }
    return *this;
}

template <typename T>
const_set_iterator<T> const_set_iterator<T>::operator -(long shift) const
{
    auto it(*this);
    it -= shift;
    return it;
}

template <typename T>
bool const_set_iterator<T>::operator !=(const const_set_iterator<T> &iterator) const
{
    return cur.lock() != iterator.cur.lock();
}

template <typename T>
bool const_set_iterator<T>::operator ==(const const_set_iterator<T> &iterator) const
{
    return cur.lock() == iterator.cur.lock();
}
//}

#endif // CONST_SET_ITERATOR_HPP
