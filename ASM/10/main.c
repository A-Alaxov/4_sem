#include <time.h>
#include <stdio.h>
#include <string.h>

#define ITERATIONS 10000

float scalar_prod(const float* a, const float* b, int size)
{
    int result = 0;
    for (int i = 0; i < size; i++)
        result += a[i] * b[i];

    return result;
}

float ins_scalar_prod(float *a, float *b , int size)
{
    float a_buf[4];
    float b_buf[4];
    size /= 4;
    float result = 0.0;
    for (; size; size--)
    {
        memcpy(a_buf, a, 4 * sizeof(float));
        memcpy(b_buf, b, 4 * sizeof(float));
		
        __asm__ volatile
		(
            "movups %[a], %%xmm0\n\t"
            "movups %[b], %%xmm1\n\t"
            "mulps %%xmm1, %%xmm0\n\t"
            "movups %%xmm0, %[a]\n\t"
			:
            : [a]"m"(*a_buf), [b]"m"(*b_buf)
            : "%xmm0", "%xmm1"
        );
		
        for (int i = 0; i < 4; i++)
            result += a_buf[i];

        a += 4;
        b += 4;
    }
    return result;
}

int main()
{
    float arr1[8] = { 3,5,6,1,2,3,-1,3 };
    float arr2[8] = { 3,5,6,1,2,3,-1,-5 };

    printf("%lf\n%lf\n", scalar_prod(arr1, arr2, 8), ins_scalar_prod(arr1, arr2, 8));
}
