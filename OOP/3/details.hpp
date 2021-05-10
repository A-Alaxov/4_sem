#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <memory>
#include "point.hpp"
#include "edge.hpp"

class details
{
public:
    details();
    ~details();

    void add_point();
    void add_edge();
    void reform();
    void get_point();
    void get_edges();

private:
    std::shared_ptr<point> points;
    std::shared_ptr<edge> edges;
};

#endif // DETAILS_HPP
