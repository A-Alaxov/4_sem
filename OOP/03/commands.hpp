#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "drawer.hpp"

class base_command
{
public:
    virtual ~base_command() = default;

    virtual void execute() = 0;
};

class load_model : public base_command
{
public:
    explicit load_model(std::string name) : name(name) {}
    void execute() override;

private:
    std::string name;
};

class load_camera : public base_command
{
public:
    explicit load_camera(std::string name) : name(name) {}
    void execute() override;

private:
    std::string name;
};

class load_scene : public base_command
{
public:
    explicit load_scene(std::string name) : name(name) {}
    void execute() override;

private:
    std::string name;
};

class draw_scene : public base_command
{
public:
    explicit draw_scene(std::shared_ptr<base_drawer> drawer) : drawer(drawer) {};
    void execute() override;

private:
    std::shared_ptr<base_drawer> drawer;
};

class reform_model : public base_command
{
public:
    explicit reform_model(long &index, point &shift, point &scale, point &rotate) : index(index), shift(shift), scale(scale), rotate(rotate) {};
    void execute() override;

private:
    long index;
    point shift;
    point scale;
    point rotate;
};

class reform_camera : public base_command
{
public:
    explicit reform_camera(long &index, point &shift, point &rotate) : index(index), shift(shift), rotate(rotate) {};
    void execute() override;

private:
    long index;
    point shift;
    point rotate;
};

class remove_model : public base_command
{
public:
    explicit remove_model(long &index) : index(index) {};
    void execute() override;

private:
    long index;
};

class remove_camera : public base_command
{
public:
    explicit remove_camera(long &index) : index(index) {};
    void execute() override;

private:
    long index;
};

class set_camera : public base_command
{
public:
    explicit set_camera(int &index) : index(index) {};
    void execute() override;

private:
    long index;
};

#endif // COMMANDS_HPP
