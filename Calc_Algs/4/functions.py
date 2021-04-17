from math import fabs
import matplotlib.pyplot as plt


def least_squares_method(table, n):
    n += 1
    matr = [[0] * (n + 1) for i in range(n)]
    coefs = []
    
    for i in range(n):
        for j in range(i, n):
            summ = 0
            for k in range(len(table)):
                summ += table[k][2] * table[k][0] ** (i + j)
            matr[i][j] = matr[j][i] = summ
            
        summ = 0
        for k in range(len(table)):
            summ += table[k][2] * table[k][1] * table[k][0] ** i
        matr[i][n] = summ

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
        for j in range(len(coefs)):
            summ -= coefs[j] * matr[i][j]
        coefs.append(summ)

    dots = []
    x = table[0][0]
    while x <= table[len(table) - 1][0]:
        y = 0
        for j in range(len(coefs)):
            y += coefs[j] * x ** j
        dots.append(y)
        x += 0.1

    return dots
