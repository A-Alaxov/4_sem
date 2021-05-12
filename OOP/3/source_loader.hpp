#ifndef SOURCE_LOADER_HPP
#define SOURCE_LOADER_HPP

#include "point.hpp"
#include "edge.hpp"

#include <vector>
#include <string>
#include <fstream>

class source_loader
{
public:
    source_loader() = default;
    ~source_loader() = default;

    virtual void open(std::string name) = 0;
    virtual void close() = 0;
    virtual bool is_open() = 0;
    virtual std::vector<point> read_points() = 0;
    virtual std::vector<edge> read_edges() = 0;
};

class file_loader : public source_loader
{
public:
    file_loader() = default;
    ~file_loader();

    void open(std::string name) override;
    void close() override;
    bool is_open() override;
    std::vector<point> read_points() override;
    std::vector<edge> read_edges() override;

private:
    std::ifstream file;
};

#endif // SOURCE_LOADER_HPP
