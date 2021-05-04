from math import fabs, sin, cos, pi, exp, sqrt
import numpy as np


def polynomial_func(polynomial, x):
    y = 0
    for i in range(len(polynomial)):
        y += polynomial[i] * x ** i
    return y


def dichotomy_method(polynomial, a, b):
    eps = 10 ** (-5)

    y1 = polynomial_func(polynomial, a)
    if fabs(y1) < eps:
        return a
    x = (b + a) / 2
    y = polynomial_func(polynomial, x)

    while fabs(y) > eps:
        if y1 * y <= 0:
            b = x
        else:
            a = x
        x = (b + a) / 2
        y = polynomial_func(polynomial, x)

    return x


def Gauss(func, M, a, b, phi, tao):
    n = M + 1

    #Нахождение узлов t
    Legendre_pol_prev = np.array([0, 1])
    Legendre_pol = np.array([-0.5, 0, 1.5])

    t = [0, sqrt(1 / 3), 1]
    for i in range(3, n + 1):
        Legendre_pol_temp = Legendre_pol.copy()
        
        Legendre_pol_prev = np.append(Legendre_pol_prev, [0, 0])
        Legendre_pol = np.insert(Legendre_pol, 0, 0)
        
        Legendre_pol = (Legendre_pol * (2*i-1) -
                        Legendre_pol_prev * (i-1)) / i

        Legendre_pol_prev = Legendre_pol_temp.copy()

        for j in range(len(t) - 1):
            t[j] = dichotomy_method(Legendre_pol, t[j], t[j + 1])
        if i % 2 == 0:
            t.insert(0, 0)

    t.remove(1)
    i = 1
    while i < len(t):
        t.insert(0, -t[i])
        i += 2
    if n % 2 == 0:
        t.remove(0)

    #Нахождение коэффициентов А
    matr = []
    for k in range(n):
        matr.append((np.array(t) ** k).tolist())
        matr[k].append((1 - (-1) ** (k + 1)) / (k + 1))

    if n % 2:
        matr[0], matr[n // 2 + 1] = matr[n // 2 + 1][:], matr[0][:]

    A = []
    for i in range(n - 1, 0, -1):
        tmp = matr[i][i]
        for j in range(n + 1):
            matr[i][j] /= tmp

        for j in range(i):
            tmp = matr[j][i]
            for k in range(n + 1):
                matr[j][k] -= matr[i][k] * tmp
    matr[0][n] /= matr[0][0]

    for i in range(n):
        summ = matr[i][n]
        for j in range(len(A)):
            summ -= A[j] * matr[i][j]
        A.append(summ)

    F = 0
    for i in range(n):
        F += A[i] * func((b + a) / 2 + (b - a) / 2 * t[i], phi, tao)
    F *= (b - a) / 2
    
    return F


def get_arg(a, b, N, i):
    return (b - a) / N * i


def sequential_integration(func, N, M, a, b, tao):
    Integral = 0

    #Формула Симпсона
    for i in range(N // 2):
        Integral += Gauss(func, M, a, b, get_arg(b, a, N, 2 * i), tao)
        Integral += 4 * Gauss(func, M, a, b, get_arg(b, a, N, 2 * i + 1), tao)
        Integral += Gauss(func, M, a, b, get_arg(b, a, N, 2 * i + 2), tao)

    return Integral * (b - a) / N / 3
