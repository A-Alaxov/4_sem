#include "funcs.hpp"
#include <math.h>

double func1(double x, double z)
{
    return sin(x) * z;
}

double func2(double x, double z)
{
    return sin(x) * cos(z);
}

double func3(double x, double z)
{
    return pow(M_E, cos(x)) * sin(z);
}

double func4(double x, double z)
{
    return fabs(cos(z)) * sin(fabs(x));
}
