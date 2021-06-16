#include "edge.hpp"

edge::edge()
{

}

edge::edge(const long point1, const long point2)
    :point1(point1), point2(point2)
{
}

long edge::get_first()
{
    return point1;
}

long edge::get_second()
{
    return point2;
}
