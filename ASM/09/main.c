#include <stdio.h>

#define PI_2    3.14
#define PI_6    3.141596

#include "test_01.h"
#include "test_02.h"
#include "test_03.h"

#define TO_STR(x) #x


void precision_cmp() 
{
    double res = 0.0;

    printf("\n\nCompare for pi:\n");

    printf(TO_STR(PI_2)" : \t%.12e\n", sin(PI_2));
    printf(TO_STR(PI_6)" : %.12e\n", sin(PI_6));

    asm(
		"finit\n"
        "fldpi\n"
        "fsin\n"
        "fstp %0\n" 
        ::"m"(res)
    );

    printf("FPU : %.12e\n", res);

    printf("\n\nCompare for pi/2:\n");
    printf(TO_STR(PI_2)" / 2 : \t%.12e\n", sin(PI_2 / 2));
    printf(TO_STR(PI_6)" / 2 : %.12e\n", sin(PI_6 / 2));

    res = 2.0;
    asm(
		"finit\n"
        "fldpi\n"
        "fld1\n"
        "fld1\n"
        "faddp\n"
        "fdiv\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res)
    );

    printf("FPU : %.12e\n", res);
}

int main(void)
{
    print_test_float();

    print_test_double();

#ifndef NO_i387
    print_test_long_double();
#endif

    precision_cmp();

    return 0;
}
