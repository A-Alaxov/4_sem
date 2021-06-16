from functions import *
import pylab


def function(teta, phi, tao):
    return 4 / pi * (1 - exp(-tao * 2 * cos(teta) /
           (1 - (sin(teta) * cos(phi)) ** 2))) * cos(teta) * sin(teta)


def main():
    M = 4
    a = 0
    b = pi / 2

    #Исследование при различном кол-ве узлов в методе Симпсона
    dots = []
    for N in range(2, 7, 2):
        temp = [[], []]
        tao = 0.05
        while tao <= 10:
            temp[0].append(tao)
            temp[1].append(sequential_integration(function, N, M, a, b, tao))
            tao += 0.05
        dots.append(temp)

    pylab.figure(1)
    pylab.plot(dots[0][0], dots[0][1], label = '3 узла сетки в методе Симпмона')
    pylab.plot(dots[1][0], dots[1][1], label = '5 узлов сетки в методе Симпмона')
    pylab.plot(dots[2][0], dots[2][1], label = '7 узлов сетки в методе Симпмона')
    pylab.legend()
    pylab.ylabel('Epsilon')
    pylab.xlabel('Tao')

    #Исследование при различном кол-ве узлов в методе Гаусса
    dots = []
    for M in range(2, 7, 2):
        temp = [[], []]
        tao = 0.05
        while tao <= 10:
            temp[0].append(tao)
            temp[1].append(sequential_integration(function, N, M, a, b, tao))
            tao += 0.05
        dots.append(temp)

    N = 4
    pylab.figure(2)
    pylab.plot(dots[0][0], dots[0][1], label = '3 узла сетки в методе Гаусса')
    pylab.plot(dots[1][0], dots[1][1], label = '5 узлов сетки в методе Гаусса')
    pylab.plot(dots[2][0], dots[2][1], label = '7 узлов сетки в методе Гаусса')
    pylab.legend()
    pylab.ylabel('Epsilon')
    pylab.xlabel('Tao')
    
    pylab.show()
    

if __name__ == "__main__":
    main()
