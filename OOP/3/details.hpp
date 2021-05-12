#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <memory>
#include <vector>

#include "point.hpp"
#include "edge.hpp"

class details
{
public:
    details() = default;
    ~details() = default;

    void add_point(point pt);
    void add_edge(edge ed);

    void reform();

    std::vector<point> get_points();
    std::vector<edge> get_edges();

private:
    std::vector<point> points;
    std::vector<edge> edges;
};

#endif // DETAILS_HPP
