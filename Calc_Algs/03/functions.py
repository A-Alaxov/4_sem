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

def spline(table, x):
    N = len(table) - 1
    h = [0, table[1][0] - table[0][0]]
    kci = [0, 0, 0]
    etta = [0, 0, 0]
    
    for i in range(2, N + 1):
        h.append(table[i][0] - table[i - 1][0])
        
        f = 3 * ((table[i][1] - table[i-1][1]) / h[i] -
                 (table[i - 1][1] - table[i-2][1]) / h[i-1])

        kci.append(-h[i] / (h[i-1] * kci[i] + 2*(h[i-1] + h[i])))
        etta.append((f - h[i-1] * etta[i]) /
                    (h[i-1] * kci[i] + 2*(h[i-1] + h[i])))
        
    c = [0, 0]
    for i in range(N - 1, 0, -1):
        c.insert(0, kci[i+1] * c[0] + etta[i+1])
    c.insert(0, 0)

    a = [0]
    b = [0]
    d = [0]
    for i in range(1, N + 1):
        a.append(table[i-1][1])
        b.append((table[i][1] - table[i - 1][1]) / h[i] - h[i] * (c[i+1] + 2*c[i])/3)
        d.append((c[i+1] - c[i]) / (3*h[i]))

    for i in range(N):
        if table[i][0] <= x and table[i+1][0] > x:
            pos = i + 1
            break
     
    return (a[pos] + b[pos] * (x - table[pos-1][0]) + c[pos] *
            (x - table[pos-1][0])**2 + d[pos] * (x - table[pos-1][0])**3)
