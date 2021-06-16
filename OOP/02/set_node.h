#ifndef SET_NODE_H
#define SET_NODE_H

#include <memory>

template <typename T>
class set_node
{
public:
    set_node() = default;
    explicit set_node(const T &data);
    set_node(const T &data, const std::shared_ptr<set_node<T>> &next, const std::shared_ptr<set_node<T>> &prev);
    explicit set_node(const std::shared_ptr<set_node<T>> &node);

    ~set_node() = default;

    void set_data(const T &data);
    void set_next(const set_node<T> &node);
    void set_next(const std::shared_ptr<set_node<T>> &node);
    void set_prev(const set_node<T> &node);
    void set_prev(const std::shared_ptr<set_node<T>> &node);

    std::shared_ptr<set_node<T>> get_next() const;
    std::shared_ptr<set_node<T>> get_prev() const;
    T &get_data();
    T *get_data_ptr();

    bool operator ==(const set_node<T> &node) const;
    bool operator ==(const std::shared_ptr<set_node<T>> &node) const;
    bool operator !=(const set_node<T> &node) const;
    bool operator !=(const std::shared_ptr<set_node<T>> &node) const;

private:
    T data;
    std::shared_ptr<set_node<T>> next;
    std::shared_ptr<set_node<T>> prev;
};

#include "set_node.hpp"

#endif // SET_NODE_H
