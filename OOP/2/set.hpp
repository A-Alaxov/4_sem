#ifndef SET_HPP
#define SET_HPP

#include <chrono>

//namespace container
//{
template  <typename T>
set<T>::set()
    :head(nullptr), tail(nullptr), size(0)
{
}

template <typename T>
bool set<T>::append(const T &data)
{
    //if (find(data))
    //    return false;

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
}
//}

#endif // SET_HPP
