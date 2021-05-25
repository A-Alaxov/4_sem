#ifndef TRANSFORM_MATRIX_H
#define TRANSFORM_MATRIX_H

#include <cmath>

#include "matrix.hpp"
#include "point.hpp"

class MoveMatrix : public Matrix<double>
{
public:
    MoveMatrix(double x, double y, double z);
    MoveMatrix(point p);
};

class ScaleMatrix : public Matrix<double>
{
public:
    ScaleMatrix(double x, double y, double z);
    ScaleMatrix(point p);
};

class RotateOxMatrix : public Matrix<double>
{
public:
    RotateOxMatrix(double angle);
};

class RotateOyMatrix : public Matrix<double>
{
public:
    RotateOyMatrix(double angle);
};

class RotateOzMatrix : public Matrix<double>
{
public:
    RotateOzMatrix(double angle);
};

#endif
