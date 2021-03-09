def neuton(func_table, x, n):
    n += 1
    
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


def mult_interp(func_table, x, y, nx, ny):
    y_table = []
    
    ny += 1
    
    i = 1
    while func_table[i][0] < y and i < len(func_table):
        i += 1

    left_part = right_part = ny // 2
    if ny % 2:
        if (y - func_table[i - 1][0]) - (func_table[i][0] - y) <= 0.000001:
            left_part += 1
        else:
            right_part += 1

    if i + right_part > len(func_table):
        left_part += i + right_part - len(func_table)

    start = max(i - left_part, 1)

    for i in range(start, start + ny):
        x_table = []
        for j in range(1, len(func_table[0])):
            x_table.append([func_table[0][j], func_table[i][j]])
        y_table.append([func_table[i][0], neuton(x_table, x, nx)])

    return neuton(y_table, y, ny - 1)
