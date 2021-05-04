def left_diff_formula(dot1, dot2):
    return ((dot1[1] - dot2[1]) /
            (dot1[0] - dot2[0]))


def left_diff(table):
    table[0].append('   -   ')
    for i in range(1, len(table)):
        table[i].append(left_diff_formula(table[i], table[i - 1]))

    
def centre_diff(table):
    table[0].append('   -   ')
    for i in range(1, len(table) - 1):
        table[i].append((table[i + 1][1] - table[i - 1][1]) /
                        (table[i + 1][0] - table[i - 1][0]))
    table[i + 1].append('   -   ')


def second_Runge(table):
    table[0].append('   -   ')
    table[1].append('   -   ')
    for i in range(2, len(table)):
        table[i].append(left_diff_formula(table[i], table[i - 1]) * 2 -
                        left_diff_formula(table[i], table[i - 2]))


def align_vars(table):
    new_table = []
    for dot in table:
        new_table.append([1 / dot[0], 1 / dot[1]])

    table[0].append('   -   ')
    for i in range(1, len(new_table)):
        table[i].append(left_diff_formula(new_table[i], new_table[i - 1]) *
                        table[i][1] ** 2 / table[i][0] ** 2)


def second_der(table):
    table[0].append('   -   ')
    for i in range(1, len(table) - 1):
        table[i].append((table[i + 1][1] + table[i - 1][1] - table[i][1] * 2) /
                        (table[i + 1][0] - table[i][0]) ** 2)
    table[i + 1].append('   -   ')
