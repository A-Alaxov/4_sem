import time
import numpy as np
import matplotlib.pyplot as plt


def cda_method(beg, end):
    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return
        
    if np.fabs(end[0] - beg[0]) >= np.fabs(end[1] - beg[1]):
        l = np.fabs(end[0] - beg[0])
    else:
        l = np.fabs(end[1] - beg[1])

    dx = (end[0] - beg[0]) / l
    dy = (end[1] - beg[1]) / l

    x = beg[0]
    y = beg[1]

    i = 1
    while i <= l + 1:
        #draw_dot((round(x), round(y)), fill = color)
        x += dx
        y += dy
        i += 1


def Brezenham_method(beg, end):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return
    
    x = beg[0]
    y = beg[1]
    dx = np.fabs(end[0] - beg[0])
    dy = np.fabs(end[1] - beg[1])
    sx = np.sign(end[0] - beg[0])
    sy = np.sign(end[1] - beg[1])
    
    if dy > dx:
        dx, dy = dy, dx
        fl = 1
    else:
        fl = 0

    m = dy / dx
    f = m - 0.5

    i = 1
    while i <= dx + 1:
        #draw_dot((x, y), fill = color)
        if f > 0:
            if fl:
                x += sx
            else:
                y += sy
            f -= 1
        if f < 0:
            if fl:
                y += sy
            else:
                x += sx
        f += m
        i += 1


def integer_Brezenham_method(beg, end):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return
    
    x = beg[0]
    y = beg[1]
    dx = np.fabs(end[0] - beg[0])
    dy = np.fabs(end[1] - beg[1])
    sx = np.sign(end[0] - beg[0])
    sy = np.sign(end[1] - beg[1])
    
    if dy > dx:
        dx, dy = dy, dx
        fl = 1
    else:
        fl = 0

    f = 2 * dy - dx

    i = 1
    while i <= dx + 1:
        #draw_dot((x, y), fill = color)
        if f > 0:
            if fl:
                x += sx
            else:
                y += sy
            f -= (2 * dx)
        if f < 0:
            if fl:
                y += sy
            else:
                x += sx
        f += (2 * dy)
        i += 1
        

def Brezenham_method_without_stairs(beg, end):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return
    
    x = beg[0]
    y = beg[1]
    dx = np.fabs(end[0] - beg[0])
    dy = np.fabs(end[1] - beg[1])
    sx = np.sign(end[0] - beg[0])
    sy = np.sign(end[1] - beg[1])
    
    if dy > dx:
        dx, dy = dy, dx
        fl = 1
    else:
        fl = 0

    m = dy / dx
    I = 1
    f = I / 2
    m *= I
    w = I - m

    #draw_dot((x, y), fill = color, alpha = f, back = back)
    i = 1
    while i <= dx:
        if f < w:
            if fl:
                y += sy
            else:
                x += sx
            f += m
        else:
            y += sy
            x += sx
            f -= w
        #draw_dot((x, y), fill = color, alpha = f, back = back)
        i += 1


def Wu_method(beg, end):
    dx = end[0] - beg[0]
    dy = end[1] - beg[1]
    if np.fabs(dy) > np.fabs(dx):
        dy, dx = dx, dy
        beg[0], beg[1] = beg[1], beg[0]
        end[0], end[1] = end[1], end[0]
        change = 1
    else:
        change = 0
        
    gradient = dy / dx

    if end[0] < beg[0]:
        beg, end = end, beg

    xpxl1 = round(beg[0])
    intery = beg[1] + gradient * (xpxl1 - beg[0])

    xpxl2 = round(end[0])

    x = xpxl1
    while x <= xpxl2 + 1:
        x_draw = x
        y_draw = int(intery)
        if change:
            x_draw, y_draw = y_draw, x_draw
        #draw_dot((x_draw, y_draw), fill = color, alpha = 1 - intery % 1, back = back)

        if change:
            x_draw += 1
        else:
            y_draw += 1
        #draw_dot((x_draw, y_draw), fill = color, alpha = intery % 1, back = back)
        intery += gradient
        x += 1


def time_compare():
    times = [0, 0, 0, 0, 0]
    funcs = [cda_method, Brezenham_method, integer_Brezenham_method,
             Brezenham_method_without_stairs, Wu_method]

    for i in range(5):
        t0 = time.clock()
        for j in range(1000):
            funcs[i]((0, 0), (599, 202))
        t1 = time.clock() - t0
        times[i] = t1

    funcs = ['Алгоритм ЦДА',
             'Алгоритм Брезенхема',
             'Целочисленный алгоритм\n\
Брезенхема',
             'Алгоритм Брезенхема с\n\
устранением ступенчатости',
             'Алгоритм Ву']

    fig, ax = plt.subplots()
    ax.barh(funcs, times)
    ax.set_yticklabels(funcs, rotation = 45)
    ax.set_xlabel('Время работы (в мс)')
    ax.set_title('Временная характеристика алгоритмов')

    for rect, cur_time in zip(ax.patches, times):
        height = rect.get_height()
        ax.annotate("{:.2f}".format(cur_time), (rect.get_width(),
                               rect.get_y() + rect.get_height() / 2),
                    xytext=(0, 5), textcoords="offset points",
                    ha='left', va='center')
    
    plt.subplots_adjust(left = 0.21, right = 0.99)
    fig.set_figwidth(8.5)
    
    plt.show()
