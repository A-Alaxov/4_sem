#ifndef SET_ITERATOR_H
#define SET_ITERATOR_H

#include <iterator>

//#include "set.h"
#include "set_node.h"

//namespace container
//{
template <typename T>
class set_iterator : std::iterator<std::bidirectional_iterator_tag, set_node<T>>
{
public:
    set_iterator();
    explicit set_iterator(const std::shared_ptr<set_node<T>> &node);
    set_iterator(const set_iterator<T> &iterator);

    ~set_iterator() = default;

    virtual void next();
    virtual void prev();

    operator bool();

    T &operator *();
    T *operator ->();
    const T &operator *() const;
    const T &operator ->() const;

    set_iterator<T> &operator =(const set_iterator<T> &iterator);

    set_iterator<T> &operator ++();
    set_iterator<T> operator ++(int);
    set_iterator<T> &operator --();
    set_iterator<T> operator --(int);

    set_iterator<T> &operator +=(long shift);
    set_iterator<T> operator +(long shift) const;
    set_iterator<T> &operator -=(long shift);
    set_iterator<T> operator -(long shift) const;

    bool operator !=(const set_iterator<T> &iterator) const;
    bool operator ==(const set_iterator<T> &iterator) const;

    template<typename U>
    friend class set;

private:
    std::weak_ptr<set_node<T>> cur;
};
//}

#include "set_iterator.hpp"

#endif // SET_ITERATOR_H
