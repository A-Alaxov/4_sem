import time
import numpy as np
from math import pi
import matplotlib.pyplot as plt
import tkinter.messagebox as msg


def cda_method(beg, end):
    stairs = 0
    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return stairs
        
    if np.fabs(end[0] - beg[0]) >= np.fabs(end[1] - beg[1]):
        l = np.fabs(end[0] - beg[0])
    else:
        l = np.fabs(end[1] - beg[1])

    dx = (end[0] - beg[0]) / l
    dy = (end[1] - beg[1]) / l

    prev = beg[1]
    if dx < dy:
        prev = beg[0]

    x = beg[0]
    y = beg[1]

    i = 1
    while i <= l + 1:
        #draw_dot((round(x), round(y)), fill = color)
        x += dx
        y += dy
        i += 1

        if np.fabs(dx) < np.fabs(dy):
            if np.fabs(round(prev) - round(x)) > 0:
                stairs += 1
        else:
            if np.fabs(round(prev) - round(y)) > 0:
                stairs += 1

        prev = y
        if np.fabs(dx) < np.fabs(dy):
            prev = x
    return stairs


def Brezenham_method(beg, end):
    stairs = 0
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        msg.showerror('Ошибка', 'Для алгоритмов Брезенхема координаты должны \
быть целочисленными')
        return stairs

    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return stairs
    
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
    x = beg[0]
    y = beg[1]

    i = 1
    while i <= dx + 1:
        #draw_dot((x, y), fill = color)
        if f > 0:
            if fl:
                x += sx
            else:
                y += sy
            f -= 1
            stairs += 1
        if f < 0:
            if fl:
                y += sy
            else:
                x += sx
        f += m
        i += 1
    return stairs


def integer_Brezenham_method(beg, end):
    stairs = 0
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        msg.showerror('Ошибка', 'Для алгоритмов Брезенхема координаты должны \
быть целочисленными')
        return stairs

    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return stairs
    
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
    x = beg[0]
    y = beg[1]

    i = 1
    while i <= dx + 1:
        #draw_dot((x, y), fill = color)
        if f > 0:
            if fl:
                x += sx
            else:
                y += sy
            f -= (2 * dx)
            stairs += 1
        if f < 0:
            if fl:
                y += sy
            else:
                x += sx
        f += (2 * dy)
        i += 1
    return stairs
        

def Brezenham_method_without_stairs(beg, end):
    stairs = 0
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        msg.showerror('Ошибка', 'Для алгоритмов Брезенхема координаты должны \
быть целочисленными')
        return stairs

    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return stairs
    
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
    x = beg[0]
    y = beg[1]
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
            stairs += 1
        #draw_dot((x, y), fill = color, alpha = f, back = back)
        i += 1
    return stairs


def Wu_method(beg, end):
    stairs = 0
    if beg[0] == end[0] and beg[1] == end[1]:
        #draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return stairs
    
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
    while x <= xpxl2:
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
        prev_intery = int(intery)
        intery += gradient
        if abs(int(intery) - prev_intery) != 0:
            stairs += 1
        x += 1
    return stairs


def stairs_research(func):
    if func == 2:
        func = cda_method
    elif func == 3:
        func = Brezenham_method
    elif func == 4:
        func = integer_Brezenham_method
    elif func == 5:
        func = Brezenham_method_without_stairs
    elif func == 6:
        func = Wu_method
    else:
        msg.showerror('Ошибка', 'Для проведения анализа нужно выбрать один \
из алгоритмов, без учёта библиотечной ф-и')
        return
                        
    stairs = [[], []]
    angle_step = (5 * pi) / 180
    i = 0
    while i < 2 * pi:
        xe = 100 * np.cos(i)
        ye = 100 * np.sin(i)

        stairs[0].append(i * 180 / pi)
        stairs[1].append(func([0, 0], [int(xe), int(ye)]))

        i += angle_step

    fig, ax = plt.subplots()

    ax.plot(stairs[0], stairs[1])
    ax.set_ylabel('Количество ступеней')
    ax.set_xlabel('Угол поворота отн. Ox')
    ax.set_title('Исследование ступенчатости (длина отрезка - 100 пикселей)')
    
    plt.show()
