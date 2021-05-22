#ifndef ERRORS_HPP
#define ERRORS_HPP


#include <exception>
#include <string>
#include <string.h>

class base_error : public std::exception
{
protected:
    std::string er_msg;

public:
    base_error(const std::string &er_msg) : er_msg(er_msg) {}

    const char *what() const noexcept override
    {
        return "Base error";
    }

    const std::string &get_info() const noexcept
    {
        return er_msg;
    }
};

class file_error : public base_error
{
public:
    file_error(const std::string &er_msg) : base_error(er_msg) {}

    const char *what() const noexcept override
    {
        return "File error";
    }
};

class builder_error : public base_error
{
public:
    builder_error(const std::string &er_msg) : base_error(er_msg) {}

    const char *what() const noexcept override
    {
        return "Builder error";
    }
};

class range_error : public base_error
{
public:
    range_error(const std::string &er_msg) : base_error(er_msg) {}

    const char *what() const noexcept override
    {
        return "Range error";
    }
};

class memory_error : public base_error
{
public:
    memory_error(const std::string &er_msg) : base_error(er_msg) {}

    const char *what() const noexcept override
    {
        return "Memory error";
    }
};

#endif // ERRORS_HPP
