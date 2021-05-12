#include "details.hpp"

void details::add_point(point pt)
{
    points.push_back(pt);
}

void details::add_edge(edge ed)
{
    edges.push_back(ed);
}

std::vector<point> details::get_points()
{
    return points;
}

std::vector<edge> details::get_edges()
{
    return edges;
}

void details::reform(point &move, point &scale, point &rotate)
{
    for (auto point : points)
    {
        point.move(move);
        point.scale(scale);
        point.rotate(rotate);
    }
}
