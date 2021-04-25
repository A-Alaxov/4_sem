#ifndef SET_EXPECTATIONS_H
#define SET_EXPECTATIONS_H

#include <exception>
#include <string>
#include <string.h>

class set_exception : public std::exception
{
protected:
    std::string er_msg;

public:
    set_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        : er_msg("\nTIME: " + time + \
                 "\nFILE: " + file_name + \
                 "\nCLASS: " + class_name + \
                 "\nMETHOD: " + method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 12];
        strcpy(cer_msg, std::string("LIST ERROR\n" + er_msg).c_str());

        return cer_msg;
    }
};

class set_memory_exception : public set_exception
{
public:
    set_memory_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        :set_exception(time, file_name, class_name, method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 14];
        strcpy(cer_msg, std::string("MEMORY ERROR\n" + er_msg).c_str());

        return cer_msg;
    }
};

class set_iterator_exception : public set_exception
{
public:
    set_iterator_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        :set_exception(time, file_name, class_name, method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 18];
        strcpy(cer_msg, std::string("INVALID ITERATOR\n" + er_msg).c_str());

        return cer_msg;
    }
};

#endif // SET_EXPECTATIONS_H
