#ifndef OBJECT_HPP
#define OBJECT_HPP


class object
{
public:
    object();
    ~object();

    virtual void accept() = 0;
    virtual bool is_composite() = 0;
    virtual bool is_visible() = 0;
    virtual void reform() = 0;
};

class visible_object : public object
{
public:
    visible_object();
    ~visible_object();

    bool is_visible() override { return true; }
};

class invisible_object : public object
{
public:
    invisible_object();
    ~invisible_object();

    bool is_visible() override { return false; }
};

#endif // OBJECT_HPP
