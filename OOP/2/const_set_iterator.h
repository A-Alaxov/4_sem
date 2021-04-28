#ifndef CONST_SET_ITERATOR_H
#define CONST_SET_ITERATOR_H

#include <iterator>

//#include "set.h"
#include "set_node.h"

//namespace container
//{
template <typename T>
class const_set_iterator : std::iterator<std::bidirectional_iterator_tag, set_node<T>>
{
public:
    const_set_iterator();
    explicit const_set_iterator(const std::shared_ptr<set_node<T>> &node);
    const_set_iterator(const const_set_iterator<T> &iterator);

    ~const_set_iterator() = default;

    virtual void next();
    virtual void prev();

    operator bool();

    const T &operator *() const;
    const T *operator ->() const;

    const_set_iterator<T> &operator =(const const_set_iterator<T> &iterator);

    const_set_iterator<T> &operator ++();
    const_set_iterator<T> operator ++(int);
    const_set_iterator<T> &operator --();
    const_set_iterator<T> operator --(int);

    const_set_iterator<T> &operator +=(long shift);
    const_set_iterator<T> operator +(long shift) const;
    const_set_iterator<T> &operator -=(long shift);
    const_set_iterator<T> operator -(long shift) const;

    bool operator !=(const const_set_iterator<T> &iterator) const;
    bool operator ==(const const_set_iterator<T> &iterator) const;

    template <typename Type>
    friend class set;

private:
    std::weak_ptr<set_node<T>> cur;
};
//}

#include "const_set_iterator.hpp"

#endif // CONST_SET_ITERATOR_H
