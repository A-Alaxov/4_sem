#include <iostream>
#include <vector>

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

template <typename T>
bool rever_cmp(const T *arr, long size, set<T> &set)
{
    long lsize = set.get_size();
    bool res = (lsize == size);
    long i = 0;
    for (auto elem = set.end(); elem != set.end(); elem--)
    {
        if (!res)
            return res;
        res = (elem == arr[i++]);
    }

    return res;
}

void test_default_constructor()
{
    std::cout << "test_default_constructor" << std::endl;
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

void test_copy_constructor()
{
    std::cout << "test_copy_constructor" << std::endl;
    try
    {
        long arr[5] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> s(arr, size);
        set<long> s1(s);
        bool test = cmp<long>(arr, size, s1);
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

void test_shallow_copy_constructor()
{
    std::cout << "test_shallow_copy_constructor" << std::endl;
    try
    {
        long arr[5] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> s1(set<long> {1, 2, 3, 4, 5});
        bool test = cmp<long>(arr, size, s1);
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

void test_init_list_constructor()
{
    std::cout << "test_init_list_constructor" << std::endl;
    try
    {
        long arr[5] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> s {1, 2, 3, 4, 5};
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

void test_array_constructor()
{
    std::cout << "test_array_constructor" << std::endl;
    try
    {
        long arr[5] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> s(arr, size);
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

void test_iterator_constructor()
{
    std::cout << "test_iterator_constructor" << std::endl;
    try
    {
        long arr[5] = {1, 2, 3, 4, 5};
        long size = 5;
        std::vector<long> vect {1, 2, 3, 4, 5};
        set<long> s(vect.begin(), vect.end());
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
    std::cout << "test_append" << std::endl;
    try
    {
        long arr[3] = {0, 1, 2};
        long size = 3;
        set<long> s;
        s.append(0);
        s.append(1);
        s.append(2);
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

void test_append_set()
{
    std::cout << "test_append_set" << std::endl;
    try
    {
        long arr[3] = {0, 1, 2};
        long size = 3;
        set<long> s1 {0, 1, 2};
        set<long> s;
        s.append(s1);
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

void test_append_init_list()
{
    std::cout << "test_append_init_list" << std::endl;
    try
    {
        long arr[3] = {0, 1, 2};
        long size = 3;
        set<long> s;
        s.append({0, 1, 2});
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

void test_subtract()
{
    std::cout << "test_subtract" << std::endl;
    try
    {
        long arr[3] = {1};
        long size = 1;
        set<long> s;
        s.append(0);
        s.append(1);
        s.append(2);
        s.subtract(2);
        s.subtract(0);
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

void test_subtract_set()
{
    std::cout << "test_subtract_set" << std::endl;
    try
    {
        long arr[3] = {0};
        long size = 1;
        set<long> s1 {1, 2};
        set<long> s {0, 1, 2};
        s.subtract(s1);
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

void test_subtract_init_list()
{
    std::cout << "test_subtract_init_list" << std::endl;
    try
    {
        long arr[3] = {0};
        long size = 1;
        set<long> s {0, 1, 2};
        s.subtract({1, 2});
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

void test_add_elem_method()
{
    std::cout << "test_add_elem_method" << std::endl;
    try
    {
        long ar[7] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        set<long> l {1, 2, 3, 4, 5};
        l.add((long) 6);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_add_set_method()
{
    std::cout << "test_add_set_method" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {6, 7, 8, 9, 10};
        l1.add(l2);
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_add_elem()
{
    std::cout << "test_add_elem" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        set<long> l {1, 2, 3, 4, 5};
        set<long> l1 = l + (long) 6;
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_add_set()
{
    std::cout << "test_add_set" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {6, 7, 8, 9, 10};
        set<long> l3 = l1 + l2;
        bool test = cmp<long>(ar, size, l3);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_add_eq_elem()
{
    std::cout << "test_add_eq_elem" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        set<long> l {1, 2, 3, 4, 5};
        l += (long) 6;
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_add_eq_set()
{
    std::cout << "test_add_eq_set" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {6, 7, 8, 9, 10};
        l1 += l2;
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sub_elem_method()
{
    std::cout << "test_sub_elem_method" << std::endl;
    try
    {
        long ar[7] = {1, 2, 3, 4};
        long size = 4;
        set<long> l {1, 2, 3, 4, 5};
        l.sub((long) 5);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sub_set_method()
{
    std::cout << "test_sub_set_method" << std::endl;
    try
    {
        long ar[10] = {1, 2};
        long size = 2;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 5, 6, 7};
        l1.sub(l2);
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sub_elem()
{
    std::cout << "test_sub_elem" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4};
        long size = 4;
        set<long> l {1, 2, 3, 4, 5};
        set<long> l1 = l - (long) 5;
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sub_set()
{
    std::cout << "test_sub_set" << std::endl;
    try
    {
        long ar[10] = {1, 2, 5};
        long size = 3;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 8, 9, 10};
        set<long> l3 = l1 - l2;
        bool test = cmp<long>(ar, size, l3);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sub_eq_elem()
{
    std::cout << "test_sub_eq_elem" << std::endl;
    try
    {
        long ar[6] = {2, 3, 4, 5};
        long size = 4;
        set<long> l {1, 2, 3, 4, 5};
        l -= (long) 1;
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sub_eq_set()
{
    std::cout << "test_sub_eq_set" << std::endl;
    try
    {
        long ar[10] = {2, 3, 4};
        long size = 3;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {1, 7, 8, 9, 5};
        l1 -= l2;
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sym_dif_elem_method()
{
    std::cout << "test_sym_dif_elem_method" << std::endl;
    try
    {
        long ar[7] = {1, 2, 3, 4};
        long size = 4;
        set<long> l {1, 2, 3, 4, 5};
        l.sym_dif((long) 5);
        bool test = rever_cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sym_dif_set_method()
{
    std::cout << "test_sym_dif_set_method" << std::endl;
    try
    {
        long ar[10] = {1, 2, 6, 7};
        long size = 4;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 5, 6, 7};
        l1.sym_dif(l2);
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sym_dif_elem()
{
    std::cout << "test_sym_dif_elem" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        set<long> l {1, 2, 3, 4, 5};
        set<long> l1 = l ^ (long) 6;
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sym_dif_set()
{
    std::cout << "test_sym_dif_set" << std::endl;
    try
    {
        long ar[10] = {2, 5, 9, 10};
        long size = 4;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 1, 9, 10};
        set<long> l3 = l1 ^ l2;
        bool test = rever_cmp<long>(ar, size, l3);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sym_dif_eq_elem()
{
    std::cout << "test_sym_dif_eq_elem" << std::endl;
    try
    {
        long ar[6] = {2, 3, 4, 5};
        long size = 4;
        set<long> l {1, 2, 3, 4, 5};
        l ^= (long) 1;
        bool test = rever_cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_sym_dif_eq_set()
{
    std::cout << "test_sym_dif_eq_set" << std::endl;
    try
    {
        long ar[10] = {2, 3, 4, 7, 8, 9};
        long size = 6;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {1, 7, 8, 9, 5};
        l1 ^= l2;
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_and_elem_method()
{
    std::cout << "test_log_and_elem_method" << std::endl;
    try
    {
        long ar[7] = {5};
        long size = 1;
        set<long> l {1, 2, 3, 4, 5};
        l.log_and((long) 5);
        bool test = rever_cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_and_set_method()
{
    std::cout << "test_log_and_set_method" << std::endl;
    try
    {
        long ar[10] = {3, 4, 5};
        long size = 3;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 5, 6, 7};
        l1.log_and(l2);
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_and_elem()
{
    std::cout << "test_log_and_elem" << std::endl;
    try
    {
        long ar[6] = {};
        long size = 0;
        set<long> l {1, 2, 3, 4, 5};
        set<long> l1 = l & (long) 6;
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_and_set()
{
    std::cout << "test_log_and_set" << std::endl;
    try
    {
        long ar[10] = {1, 3, 4};
        long size = 3;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 1, 9, 10};
        set<long> l3 = l1 & l2;
        bool test = rever_cmp<long>(ar, size, l3);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_and_eq_elem()
{
    std::cout << "test_log_and_eq_elem" << std::endl;
    try
    {
        long ar[6] = {1};
        long size = 1;
        set<long> l {1, 2, 3, 4, 5};
        l &= (long) 1;
        bool test = rever_cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_and_eq_set()
{
    std::cout << "test_log_and_eq_set" << std::endl;
    try
    {
        long ar[10] = {1, 5};
        long size = 2;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {1, 7, 8, 9, 5};
        l1 &= l2;
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_or_elem_method()
{
    std::cout << "test_log_or_elem_method" << std::endl;
    try
    {
        long ar[7] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> l {1, 2, 3, 4, 5};
        l.log_or((long) 5);
        bool test = rever_cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_or_set_method()
{
    std::cout << "test_log_or_set_method" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7};
        long size = 7;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 5, 6, 7};
        l1.log_or(l2);
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_or_elem()
{
    std::cout << "test_log_or_elem" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        set<long> l {1, 2, 3, 4, 5};
        set<long> l1 = l | (long) 6;
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_or_set()
{
    std::cout << "test_log_or_set" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 9, 10};
        long size = 7;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {3, 4, 1, 9, 10};
        set<long> l3 = l1 | l2;
        bool test = rever_cmp<long>(ar, size, l3);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_or_eq_elem()
{
    std::cout << "test_log_or_eq_elem" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> l {1, 2, 3, 4, 5};
        l |= (long) 1;
        bool test = rever_cmp<long>(ar, size, l);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_log_or_eq_set()
{
    std::cout << "test_log_or_eq_set" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 7, 8, 9};
        long size = 8;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {1, 7, 8, 9, 5};
        l1 |= l2;
        bool test = rever_cmp<long>(ar, size, l1);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_find()
{
    std::cout << "test_find" << std::endl;
    try
    {
        set<long> l1 {1, 2, 3, 4, 5};
        bool test = l1.find(3);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_assignment()
{
    std::cout << "test_assignment" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2;
        l2 = l1;
        bool test = rever_cmp<long>(ar, size, l2);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_shallow_assignment()
{
    std::cout << "test_shallow_assignment" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5};
        long size = 5;
        set<long> l2 = set<long> {1, 2, 3, 4, 5};
        bool test = rever_cmp<long>(ar, size, l2);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_equal()
{
    std::cout << "test_assignment" << std::endl;
    try
    {
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {1, 2, 3, 4, 5};
        l2 = l1;
        bool test = (l1 == l2);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_not_equal()
{
    std::cout << "test_not_equal" << std::endl;
    try
    {
        set<long> l1 {1, 2, 3, 4, 5};
        set<long> l2 {1, 2, 3, 4, 5};
        l2 = l1;
        bool test = !(l1 != l2);
        if (test)
            std::cout << "Passed\n" << std::endl;
        else
            std::cout << "Failed\n" << std::endl;
    }
    catch (set_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

int main()
{
    test_default_constructor();
    test_copy_constructor();
    test_shallow_copy_constructor();
    test_init_list_constructor();
    test_array_constructor();
    test_iterator_constructor();

    test_append();
    test_append_set();
    test_append_init_list();
    test_subtract();
    test_subtract_set();
    test_subtract_init_list();

    test_add_elem_method();
    test_add_set_method();
    test_add_elem();
    test_add_set();
    test_add_eq_elem();
    test_add_eq_set();

    test_sub_elem_method();
    test_sub_set_method();
    test_sub_elem();
    test_sub_set();
    test_sub_eq_elem();
    test_sub_eq_set();

    test_sym_dif_elem_method();
    test_sym_dif_set_method();
    test_sym_dif_elem();
    test_sym_dif_set();
    test_sym_dif_eq_elem();
    test_sym_dif_eq_set();

    test_log_and_elem_method();
    test_log_and_set_method();
    test_log_and_elem();
    test_log_and_set();
    test_log_and_eq_elem();
    test_log_and_eq_set();

    test_log_or_elem_method();
    test_log_or_set_method();
    test_log_or_elem();
    test_log_or_set();
    test_log_or_eq_elem();
    test_log_or_eq_set();

    test_assignment();
    test_shallow_assignment();
    test_equal();
    test_not_equal();
    test_find();
}
