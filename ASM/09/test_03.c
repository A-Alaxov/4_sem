#include "test_03.h"

#define REPEAT_CNT 10000000

#include <time.h>

#ifndef NO_i387

void test_long_double(void);

void print_test_long_double(void)
{
    printf("Long double (80-bit) test:\n");

    clock_t begin, end;

    begin = clock();
    test_long_double();
    end = clock();

    printf("%lf us.", (double) (end - begin) / CLOCKS_PER_SEC / 10);
	
	begin = clock();
    test_long_double_asm();
    end = clock();

    printf("\t%lf us.\n", (double) (end - begin) / CLOCKS_PER_SEC / 10);
}

void test_long_double(void)
{
    long double a = 3.141592e30;

    for (int i = 0; i < REPEAT_CNT; ++i)
    {
        a *= 1.9321;
        a += 1.4556;
    }
}

void test_long_double_asm(void)
{
    long double a = 3.141592e30;
    long double x1 = 1.9321;
    long double x2 = 1.4556;

    for (int i = 0; i < REPEAT_CNT; ++i)
    {
        __asm__(
            "xor %%rdx, %%rdx;\n\t"
            "fld %0;\n\t"
            "fld %1;\n\t"
            "faddp;\n\t"
            "fld %2;\n\t"
            "fmulp;\n\t"
            "fstp %0;\n\t"
            :: "g"(a), "g"(x1), "g"(x2)
            : "%rax", "%rbx", "%rcx", "%rdx"
        );
    }
}

#endif