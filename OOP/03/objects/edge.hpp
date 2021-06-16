#ifndef EDGE_HPP
#define EDGE_HPP


class edge
{
public:
    edge();
    edge(const long point1, const long point2);
    ~edge() = default;

    long get_first();
    void set_first(long index);

    long get_second();
    void set_second(long index);

private:
    long point1;
    long point2;
};

#endif // EDGE_HPP
