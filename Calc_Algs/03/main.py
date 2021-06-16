from functions import *

def main():
    func_table = []

    for i in range(11):
        func_table.append([i, i**2])
    
    x = 5.5
    
    print('Заданная таблица:\n\
| X |Y(x)|')
    for i in func_table:
        print('|{:3d}|{:4d}|'.format(i[0], i[1]))

    print('\nЗаданный аргумент: X =', x)
    
    print('Результат интерполяции кубическим сплайном: {:.6f}'.format(spline(func_table, x)))
    print('Точное значение: {:.2f}'.format(x**2))
    print('Результат интерполяции полиномом Ньютона 3-ей степени: {:.6f}'.format(neuton(func_table, x, 3)))

if __name__ == "__main__":
    main()
