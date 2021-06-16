#ifndef SET_NODE_HPP
#define SET_NODE_HPP

template  <typename T>
set_node<T>::set_node(const T &data)
    :data(data), next(nullptr), prev(nullptr)
{
}


template  <typename T>
set_node<T>::set_node(const T &data, const std::shared_ptr<set_node<T>> &next, const std::shared_ptr<set_node<T>> &prev)
    :data(data), next(next), prev(prev)
{
}

template  <typename T>
set_node<T>::set_node(const std::shared_ptr<set_node<T>> &node)
    :data(node->data), next(node->next), prev(node->prev)
{
}

template  <typename T>
void set_node<T>::set_next(const set_node<T> &node)
{
    next = std::make_shared<set_node<T>>(node);
}

template  <typename T>
void set_node<T>::set_next(const std::shared_ptr<set_node<T>> &node)
{
    next = node;
}

template  <typename T>
void set_node<T>::set_prev(const set_node<T> &node)
{
    prev = std::make_shared<set_node<T>>(node);
}

template  <typename T>
void set_node<T>::set_prev(const std::shared_ptr<set_node<T>> &node)
{
    prev = node;
}

template  <typename T>
std::shared_ptr<set_node<T>> set_node<T>::get_next() const
{
    return next;
}

template  <typename T>
std::shared_ptr<set_node<T>> set_node<T>::get_prev() const
{
    return prev;
}

template <typename T>
T &set_node<T>::get_data()
{
    return data;
}

template <typename T>
T *set_node<T>::get_data_ptr()
{
    return &data;
}

template <typename T>
bool set_node<T>::operator ==(const set_node<T> &node) const
{
    bool res = (this->data == node.data);
    if (res)
    {
        res = (this->next == node.next);
    }
    return res;
}

template <typename T>
bool set_node<T>::operator ==(const std::shared_ptr<set_node<T>> &node) const
{
    return this == node;
}

template <typename T>
bool set_node<T>::operator !=(const set_node<T> &node) const
{
    bool res = (this->data != node.data);
    if (res)
    {
        res = (this->next != node.next);
    }
    return res;
}

template <typename T>
bool set_node<T>::operator !=(const std::shared_ptr<set_node<T>> &node) const
{
    return this != node;
}

#endif // SET_NODE_HPP
