from valg_1 import *

def main():
    func_table = [[0.00,  1.000000, -1.00000],
            [0.15,  0.838771, -1.14944],
            [0.30,  0.655336, -1.29552],
            [0.45,  0.450447, -1.43497],
            [0.60,  0.225336, -1.56464],
            [0.75, -0.018310, -1.68164],
            [0.90, -0.278390, -1.78333],
            [1.05, -0.552430, -1.86742]]
    
    x = 0.525
    
    print('Заданная таблица:\n\
|  X  |   Y(x)   |    Y\'    |')
    for i in func_table:
        print('|{:5.2f}|{:10.6f}|{:10.6f}|'.format(i[0], i[1], i[2]))

    print('\n\nЗначения полиномов при X = 0.525:\n\
| Полином |   n = 1   |   n = 2   |   n = 3   |   n = 4   |')
    
    print('| Ньютона |', end = '')
    for i in range(1, 5):
        print('{:10.6f} |'.format(neuton(func_table, x, i)), end = '')

    print('\n| Эрмита  |', end = '')
    for i in range(1, 5):
        print('{:10.6f} |'.format(hermit(func_table, x, i)), end = '')

    print('\n\nНахождение корня функции обратной интерполяцией, \
используя полином Ньютона:\n\
|   n = 1   |   n = 2   |   n = 3   |   n = 4   |\n|', end = '')
    for i in range(1, 5):
        print('{:10.6f} |'.format(find_root(func_table, i)), end = '')

    n = int(input('\n\nВведите степень полинома: '))
    x = float(input('Введите значение X: '))

    print('\nЗначение, полученное полиномом Ньютона: {:.6f}\n\
Значение, полученное полиномом Эрмита: {:.6f}'.format(neuton(func_table, x, n),
                                                      hermit(func_table, x, n)))

if __name__ == "__main__":
    main()
