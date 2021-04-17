from functions import *

def main():
    
    func_table = [[0, 0, 1],
                  [1, -1.5, 1],
                  [2, -1, 1],
                  [3, 2.5, 1],
                  [4, 6, 1],
                  [5, 8, 1],
                  [6, 7, 1],
                  [7, 5, 1],
                  [8, 5, 1],
                  [9, 7.5, 1],
                  [10, 11.5, 1]]
    '''
    func_table = [[0, 0, 4],
                  [1, -1.5, 3],
                  [2, -1, 7],
                  [3, 2.5, 11],
                  [4, 6, 1],
                  [5, 8, 5],
                  [6, 7, 23],
                  [7, 5, 1],
                  [8, 5, 2],
                  [9, 7.5, 1],
                  [10, 11.5, 99]]
    '''
    print('Заданная таблица:\n\
| №| X |Y(x)|Вес|')
    for i in range(len(func_table)):
        print('|{:2d}|{:3d}|{:4.1f}|{:3d}|'.format(i + 1,
                                                   func_table[i][0],
                                                   func_table[i][1],
                                                   func_table[i][2]))

    print('\n1 - Изменить вес точки\n\
2 - Вывести таблицу\n\
3 - Вывести графики для разных степерей полинома\n\
4 - Вывести графики для текущей таблицы и аналогичной, с весом 1 у всех узлов\n\
0 - Выйти из меню\n\
Выбор: ', end = '')
    choice = int(input())

    while choice:
        if choice == 1:
            num = int(input('\nВведите номер точки: '))
            weight = int(input('\nВведите новый вес точки: '))
            func_table[num - 1][2] = weight
        elif choice == 2:
            print('Заданная таблица:\n\
| №| X |Y(x)|Вес|')
            for i in range(len(func_table)):
                print('|{:2d}|{:3d}|{:4.1f}|{:3d}|'.format(i + 1,
                                                   func_table[i][0],
                                                   func_table[i][1],
                                                   func_table[i][2]))
        elif choice == 3:
            graph(func_table)
        else:
            graph_compare(func_table)
        print('\n1 - Изменить вес точки\n\
2 - Вывести таблицу\n\
3 - Вывести графики для разных степерей полинома\n\
4 - Вывести графики для текущей таблицы и аналогичной, с весом 1 для всех узлов\n\
0 - Выйти из меню\n\
Выбор: ', end = '')
        choice = int(input())

def graph(func_table):
    dots = [[]]
    x = func_table[0][0]
    while x <= func_table[len(func_table) - 1][0]:
        dots[0].append(x)
        x += 0.1

    dots.append(least_squares_method(func_table, 1))
    dots.append(least_squares_method(func_table, 2))
    dots.append(least_squares_method(func_table, 4))
    dots.append(least_squares_method(func_table, 6))

    funcs = ['p = 1',
             'p = 2',
             'p = 4',
             'p = 6',
             'Данные']

    fig, ax = plt.subplots()

    ax.plot(dots[0], dots[1],
            dots[0], dots[2],
            dots[0], dots[3],
            dots[0], dots[4])
    ax.scatter([i[0] for i in func_table], [i[1] for i in func_table],
               c = 'black')

    plt.legend(funcs, loc=2)
    plt.grid()
    
    ax.set_ylabel('Y')
    ax.set_xlabel('X')
    
    plt.show()

def graph_compare(func_table):
    dots = [[]]
    x = func_table[0][0]
    while x <= func_table[len(func_table) - 1][0]:
        dots[0].append(x)
        x += 0.1

    dots.append(least_squares_method(func_table, 1))
    dots.append(least_squares_method(func_table, 2))

    for i in range(len(func_table)):
        func_table[i][2] = 1
    dots.append(least_squares_method(func_table, 1))
    dots.append(least_squares_method(func_table, 2))

    funcs = ['p = 1 (вес точек различный)',
             'p = 2 (вес точек различный)',
             'p = 1 (вес точек равен 1)',
             'p = 2 (вес точек равен 1)',
             'Данные']

    fig, ax = plt.subplots()

    ax.plot(dots[0], dots[1],
            dots[0], dots[2],
            dots[0], dots[3],
            dots[0], dots[4])
    ax.scatter([i[0] for i in func_table], [i[1] for i in func_table],
               c = 'black')

    plt.legend(funcs, loc=2)
    plt.grid()
    
    ax.set_ylabel('Y')
    ax.set_xlabel('X')
    
    plt.show()

if __name__ == "__main__":
    main()
