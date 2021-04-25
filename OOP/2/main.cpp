#include <iostream>

#include "set.h"

//using namespace container;

template <typename T>
bool cmp(const T *arr, long size, set<T> &set)
{
    long lsize = set.get_size();
    bool res = (lsize == size);
    long i = 0;
    for (auto elem : set)
    {
        if (!res)
            return res;
        res = (elem == arr[i++]);
    }

    return res;
}

void test_default_constructor()
{
    std::cout << "Test_default_constructor" << std::endl;
    try
    {
        long *arr = nullptr;
        long size = 0;
        set<long> s;
        bool test = cmp<long>(arr, size, s);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception  &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_append()
{
    std::cout << "Test_append" << std::endl;
    try
    {
        long arr[3] = {0, 1, 2};
        long size = 3;
        set<long> s;
        s.append(0);
        s.append(1);
        s.append(2);
        bool test = cmp<long>(arr, size, s);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception  &error)
    {
        std::cout << error.what() << std::endl;
    }
}

int main()
{
    test_default_constructor();
    test_append();
}
