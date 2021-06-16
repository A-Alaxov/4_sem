#include "test_01.h"

#define REPEAT_CNT 10000000

#include <time.h>

void print_test_float(void)
{
    printf("Float (32-bit) test:\n");

    clock_t begin, end;

    begin = clock();
    test_float();
    end = clock();

    printf("C - %lf us.", (double) (end - begin) / CLOCKS_PER_SEC / 10);
	
	begin = clock();
    test_float_asm();
    end = clock();
	
	printf("\tASM - %lf us.\n\n", (double) (end - begin) / CLOCKS_PER_SEC / 10);
}

void test_float(void)
{
    float a = 3.141592e30;

    for (int i = 0; i < REPEAT_CNT; ++i)
    {
        a *= 1.9321;
        a += 1.4556;
    }
}

void test_float_asm(void)
{
    float a = 3.141592e30;
    float x1 = 1.9321;
    float x2 = 1.4556;

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
