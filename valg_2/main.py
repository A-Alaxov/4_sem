from functions import *

def main():
    func_table = [[0,  0,  1,  2,  3,  4],
                  [0,  0,  1,  4,  9, 16],
                  [1,  1,  2,  5, 10, 17],
                  [2,  4,  5,  8, 13, 20],
                  [3,  9, 10, 13, 18, 25],
                  [4, 16, 17, 20, 25, 32]]
    
    x = 1.5
    y = 1.5
    
    print('Заданная таблица:\n|Y\X|', end = '')
    for i in range(1, len(func_table[0])):
        print('{:^10.0f}|'.format(func_table[0][i]), end = '')
    for i in range(1, len(func_table)):
        print('\n|{:^3.0f}|'.format(func_table[i][0]), end = '')
        for j in func_table[i][1:]:
            print('{:^10.2f}|'.format(j), end = '')

    print('\n\nРезультат многомерной интерполяции при X = 1.5; Y = 1.5:\n\
|   n = 1   |   n = 2   |   n = 3   |\n|', end = '')
    
    for i in range(1, 4):
        print('{:10.6f} |'.format(mult_interp(func_table, x, y, i, i)),
              end = '')

    nx = int(input('\n\nВведите степень nx полинома: '))
    ny = int(input('Введите степень ny полинома: '))
    x = float(input('Введите значение X: '))
    y = float(input('Введите значение Y: '))

    print('\nЗначение, полученное многомерной \
интерполяцией: {:.6f}'.format(mult_interp(func_table, x, y, nx, ny)))

if __name__ == "__main__":
    main()
