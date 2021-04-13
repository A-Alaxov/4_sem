from math import fabs


def copy_table(table):
    new = []
    for i in table:
        new.append(i[:])

    return new


def neuton(table, x, n):
    n += 1
    func_table = copy_table(table)
    
    i = 0
    while func_table[i][0] < x and i < len(func_table):
        i += 1

    left_part = right_part = n // 2
    if n % 2:
        if (x - func_table[i - 1][0]) - (func_table[i][0] - x) <= 0.000001:
            left_part += 1
        else:
            right_part += 1

    if i + right_part > len(func_table):
        left_part += i + right_part - len(func_table)

    start = max(i - left_part, 0)

    for j in range(1, n):
        for i in range(start + n - 1, start + j - 1, -1):
            func_table[i][1] = ((func_table[i][1] - func_table[i - 1][1]) /
                                (func_table[i][0] - func_table[i - j][0]))

    result = 0
    for i in range(start, start + n):
        mult = func_table[i][1]
        for j in range(start, i):
            mult *= (x - func_table[j][0])
        result += mult

    return result


def hermit_table(table):
    new = []
    for i in table:
        new.append(i[:])
        new.append(i[:])

    return new


def hermit(table, x, n):
    n += 1
    func_table = hermit_table(table)
    
    i = 0
    while func_table[i][0] < x and i < len(func_table):
        i += 1

    left_part = right_part = n // 2
    if n % 2:
        if (x - func_table[i - 1][0]) - (func_table[i][0] - x) <= 0.000001:
            left_part += 1
        else:
            right_part += 1

    if i + right_part > len(func_table):
        left_part += i + right_part - len(func_table)

    start = max(i - left_part, 0)

    for i in range(start + n - 1, start, -1):
        if fabs(func_table[i][0] - func_table[i - 1][0]) < 0.000001:
            func_table[i][1] = func_table[i][2]
        else:
            func_table[i][1] = ((func_table[i][1] - func_table[i - 1][1]) /
                                (func_table[i][0] - func_table[i - 1][0]))

    for j in range(2, n):
        for i in range(start + n - 1, start + j - 1, -1):
            func_table[i][1] = ((func_table[i][1] - func_table[i - 1][1]) /
                                (func_table[i][0] - func_table[i - j][0]))

    result = 0
    for i in range(start, start + n):
        mult = func_table[i][1]
        for j in range(start, i):
            mult *= (x - func_table[j][0])
        result += mult

    return result


def selection_sort(table):
    for i in range(len(table) - 1):
        smallest = i
        for j in range(i + 1, len(table)):
            if table[j][0] < table[smallest][0]:
                smallest = j
        table[i], table[smallest] = table[smallest], table[i]


def find_root(table, n):
    func_table = copy_table(table)
    for i in func_table:
        temp = i[0]
        i[0] = i[1]
        i[1] = temp

    selection_sort(func_table)

    return neuton(func_table, 0, n)
