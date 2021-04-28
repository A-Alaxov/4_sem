#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <chrono>
//#include "set.h"

//namespace container
//{
template  <typename T>
set<T>::set()
    :head(nullptr), tail(nullptr), size(0)
{
}

template  <typename T>
set<T>::set(const set<T> &s)
    :head(std::shared_ptr<set_node<T>>()),
     tail(std::shared_ptr<set_node<T>>()),
     size(0)
{
    for (auto it = s.cbegin(); it != s.cend(); it++)
        append(*it);
}

template  <typename T>
set<T>::set(set<T> &&s) noexcept
{
    size = s.size;
    head = s.head;
    tail = s.tail;
}

template  <typename T>
set<T>::set(const T *arr, long len)
    :head(std::shared_ptr<set_node<T>>()),
     tail(std::shared_ptr<set_node<T>>()),
     size(0)
{
    if ((len <= 0) or (!arr))
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw set_creation_by_array_exception(ctime(&timenow), __FILE__, typeid(set).name(), __FUNCTION__);
    }

    for (long i = 0; i < len; i++)
    {
        append(arr[i]);
    }

    size = len;
}

template  <typename T>
set<T>::set(const std::initializer_list<T> &elems)
    :head(std::shared_ptr<set_node<T>>()),
     tail(std::shared_ptr<set_node<T>>()),
     size(0)
{
    for (auto it : elems)
        append(it);
}

template  <typename T>
template <typename iter>
set<T>::set(iter begin, iter end)
    :head(std::shared_ptr<set_node<T>>()),
     tail(std::shared_ptr<set_node<T>>()),
     size(0)
{
    for (iter it = begin; it != end; it++)
        append(*it);
}

template <typename T>
bool set<T>::append(const T &data)
{
    if (find(data))
        return false;

    std::shared_ptr<set_node<T>> node;

    try
    {
        node = std::shared_ptr<set_node<T>>(new set_node<T>(data, std::shared_ptr<set_node<T>>(), tail));
    }
    catch (std::bad_alloc &error)
    {
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw set_memory_exception(ctime(&timenow), __FILE__, typeid(set).name(), __FUNCTION__);
    }

    if (!size)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->set_next(node);
        tail = node;
    }

    size++;
    return true;
}

template <typename T>
void set<T>::append(const set<T> &s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        append(*it);
}

template <typename T>
void set<T>::append(std::initializer_list<T> elems)
{
    for (auto it : elems)
        append(it);
}

template <typename T>
bool set<T>::subtract(const T &data)
{
    const_set_iterator<T> it = find(data);
    if (!it)
        return false;

    auto node = std::make_shared<set_node<T>>(it.cur.lock());

    if (size == 1)
    {
        head = std::shared_ptr<set_node<T>>();
        tail = std::shared_ptr<set_node<T>>();
    }
    else if (node->get_data() == head->get_data())
    {
        head = node->get_next();
        head->set_prev(nullptr);
    }
    else if (node->get_data() == tail->get_data())
    {
        tail = node->get_prev();
        tail->set_next(nullptr);
    }
    else
    {
        node->get_next()->set_prev(node->get_prev());
        node->get_prev()->set_next(node->get_next());
    }

    size--;
    return true;
}

template <typename T>
void set<T>::subtract(const set<T> &s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        subtract(*it);
}

template <typename T>
void set<T>::subtract(std::initializer_list<T> elems)
{
    for (auto it : elems)
        subtract(it);
}

template <typename T>
set<T> &set<T>::add(const set<T> &s)
{
    set<T> temp(*this + s);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::add(const T &data)
{
    set<T> temp(*this + data);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::sub(const set<T> &s)
{
    set<T> temp(*this - s);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::sub(const T &data)
{
    set<T> temp(*this - data);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::sym_dif(const set<T> &s)
{
    set<T> temp(*this ^ s);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::sym_dif(const T &data)
{
    set<T> temp(*this ^ data);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::log_and(const set<T> &s)
{
    set<T> temp(*this & s);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::log_and(const T &data)
{
    set<T> temp(*this & data);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::log_or(const set<T> &s)
{
    set<T> temp(*this | s);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::log_or(const T &data)
{
    set<T> temp(*this | data);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> set<T>::operator +(const set<T> &s)
{
    set<T> temp(*this);
    temp += s;
    return temp;
}

template <typename T>
set<T> set<T>::operator +(const T &data)
{
    set<T> temp(*this);
    temp += data;
    return temp;
}

template <typename T>
set<T> &set<T>::operator +=(const set<T> &s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        append(*it);
    return *this;
}

template <typename T>
set<T> &set<T>::operator +=(const T &data)
{
    append(data);
    return *this;
}

template <typename T>
set<T> set<T>::operator -(const set<T> &s)
{
    set<T> temp(*this);
    temp -= s;
    return temp;
}

template <typename T>
set<T> set<T>::operator -(const T &data)
{
    set<T> temp(*this);
    temp -= data;
    return temp;
}

template <typename T>
set<T> &set<T>::operator -=(const set<T> &s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        subtract(*it);
    return *this;
}

template <typename T>
set<T> &set<T>::operator -=(const T &data)
{
    subtract(data);
    return *this;
}

template <typename T>
set<T> set<T>::operator ^(const set<T> &s)
{
    set<T> temp;
    for (auto it : *this)
        if (!s.find(it))
            temp.append(it);

    for (auto it : s)
        if (!find(it))
            temp.append(it);
    return temp;
}

template <typename T>
set<T> set<T>::operator ^(const T &data)
{
    set<T> temp(*this);
    if (find(data))
        temp -= data;
    else
        temp += data;
    return temp;
}

template <typename T>
set<T> &set<T>::operator ^=(const set<T> &s)
{
    set<T> temp(*this ^ s);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::operator ^=(const T &data)
{
    subtract(data);
    return *this;
}

template <typename T>
set<T> set<T>::operator &(const set<T> &s)
{
    set<T> temp;

    for (auto it : *this)
        if (s.find(it))
            temp.append(it);

    return temp;
}

template <typename T>
set<T> set<T>::operator &(const T &data)
{
    set<T> temp;
    if (find(data))
        temp.append(data);
    return temp;
}

template <typename T>
set<T> &set<T>::operator &=(const set<T> &s)
{
    set<T> temp(*this & s);

    clear();
    for (auto it = temp.begin(); it != temp.end(); it++)
        append(*it);

    return *this;
}

template <typename T>
set<T> &set<T>::operator &=(const T &data)
{
    if (find(data))
    {
        clear();
        append(data);
    }
    else
        clear();
    return *this;
}

template <typename T>
set<T> set<T>::operator |(const set<T> &s)
{
    set<T> temp(*this);
    temp |= s;
    return temp;
}

template <typename T>
set<T> set<T>::operator |(const T &data)
{
    set<T> temp(*this);
    temp |= data;
    return temp;
}

template <typename T>
set<T> &set<T>::operator |=(const set<T> &s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        append(*it);
    return *this;
}

template <typename T>
set<T> &set<T>::operator |=(const T &data)
{
    append(data);
    return *this;
}

template <typename T>
set<T> &set<T>::operator =(const set<T> &s)
{
    clear();
    for (auto it = s.cbegin(); it != s.cend(); it++)
        append(*it);
    return *this;
}

template <typename T>
set<T> &set<T>::operator =(set<T> &&s) const
{
    clear();
    size = s.size;
    head = s.head;
    tail = s.tail;

    return *this;
}

template <typename T>
bool set<T>::operator ==(const set<T> &s) const
{
    return !(*this ^ s);
}

template <typename T>
bool set<T>::operator !=(const set<T> &s) const
{
    return (*this ^ s);
}

template <typename T>
const_set_iterator<T> set<T>::find(const T &data) const
{
    for (auto elem = begin(); elem != end(); elem++)
    {
        if (*elem == data)
            return const_set_iterator<T>(elem);
    }
    return end();
}

template <typename T>
long set<T>::get_size() const
{
    return size;
}

template <typename T>
set_iterator<T> set<T>::begin()
{
    set_iterator<T> it(head);
    return it;
}

template <typename T>
set_iterator<T> set<T>::end()
{
    set_iterator<T> it(tail);
    return ++it;
}

template <typename T>
const_set_iterator<T> set<T>::begin() const
{
    const_set_iterator<T> it(head);
    return it;
}

template <typename T>
const_set_iterator<T> set<T>::end() const
{
    const_set_iterator<T> it(tail);
    return ++it;
}

template <typename T>
const_set_iterator<T> set<T>::cbegin() const
{
    const_set_iterator<T> it(head);
    return it;
}

template <typename T>
const_set_iterator<T> set<T>::cend() const
{
    const_set_iterator<T> it(tail);
    return ++it;
}

template <typename T>
bool set<T>::is_empty() const
{
    return !size;
}

template <typename T>
void set<T>::clear()
{
    while (head)
    {
        std::shared_ptr<set_node<T>> temp = head;
        head = head->get_next();
        temp->set_next(nullptr);
    }
    size = 0;
}

template <typename T>
set<T>::operator bool() const
{
    return size;
}
//}

#endif // SET_HPP
