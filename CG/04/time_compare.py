import time
import numpy as np
import matplotlib.pyplot as plt


def canonical_eq(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return

    mid = int(round(rad / np.sqrt(2)))

    dot = [0, rad]
    #sym_oct(dot, centre, color, canv)
    for x in range(mid + 1):
        dot[0] = x
        dot[1] = round(np.sqrt(rad * rad - x * x))
        #sym_oct(dot, centre, color, canv)


def parametric_eq(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return

    dot = [rad, 0]
    count = int(round(np.pi / 4 * rad))
    t = 0
    #sym_oct(dot, centre, color, canv)
    for i in range(count + 1):
        dot[0] = round(rad * np.cos(t))
        dot[1] = round(rad * np.sin(t))
        #sym_oct(dot, centre, color, canv)
        t += 1 / rad


def Brezenham_method(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return

    X = 0
    Y = rad
    D = 2 * (1 - rad)
    Yk = rad / np.sqrt(2)
    #sym_oct([X, Y], centre, color, canv)
    while Y >= Yk:
        if D < 0:
            D1 = 2 * D + 2 * Y - 1
            if D1 < 0:
                X += 1
                D += 2 * X + 1
            else:
                X += 1
                Y -= 1
                D += 2 * (X - Y + 1)
        elif D == 0:
            X += 1
            Y -= 1
            D += 2 * (X - Y + 1)
        else:
            D2 = 2 * D - 2 * X - 1
            if D2 <= 0:
                X += 1
                Y -= 1
                D += 2 * (X - Y + 1)
            else:
                Y -= 1
                D += -2 * Y + 1
        #sym_oct([X, Y], centre, color, canv)


def midpoint_method(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    x = 0
    y = rad
    p = 1.25 - rad
    while x <= y:
        #sym_oct([x, y], centre, color, canv)
        if p >= 0:
            y -= 1
            p -= 2 * y
        x += 1
        p += 2 * x + 1


def time_compare():
    data = [[i for i in range(50, 550, 50)]]
    funcs = [canonical_eq, parametric_eq, Brezenham_method,
             midpoint_method]

    tmp = []
    for i in range(4):
        tmp.clear()
        for rad in data[0]:
            t0 = time.clock()
            for j in range(1000):
                funcs[i]((0, 0), rad, '', '')
            t1 = time.clock() - t0
            tmp.append(t1 * 10)
        data.append(tmp[:])
    
    funcs = ['Каноническое ур-е',
             'Параметрическое ур-е',
             'Алгоритм Брезенхема',
             'Алгоритм средней точки']

    fig, ax = plt.subplots()

    ax.plot(data[0], data[1],
            data[0], data[2],
            data[0], data[3],
            data[0], data[4])

    plt.legend(funcs, loc=2)
    
    ax.set_ylabel('Время в мс')
    ax.set_xlabel('Радиус окружности')
    ax.set_title('Временные характеристики алгоритмов')
    
    plt.show()


def canonical_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])
    a2 = axes[0] * axes[0]
    b2 = axes[1] * axes[1]

    xfin = int(round(a2 / np.sqrt(a2 + b2)))
    yfir = int(round(b2 / np.sqrt(a2 + b2)))

    dot = [0, axes[1]]
    #sym_ox(dot, centre, color, canv)
    for x in range(xfin):
        dot[0] = x
        dot[1] = round(np.sqrt(1 - x * x / a2) * axes[1])
        #sym_ox(dot, centre, color, canv)

    for y in range(yfir + 1, -1, -1):
        dot[1] = y
        dot[0] = round(np.sqrt(1 - y * y / b2) * axes[0])
        #sym_ox(dot, centre, color, canv)


def parametric_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])

    dot = [axes[0], 0]
    t = 0
    max_axis = max(axes)
    count = int(round(np.pi / 2 * max_axis))

    #sym_ox(dot, centre, color, canv)
    for i in range(count + 1):
        dot[0] = round(axes[0] * np.cos(t))
        dot[1] = round(axes[1] * np.sin(t))
        #sym_ox(dot, centre, color, canv)
        t += 1 / max_axis


def Brezenham_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])

    X = 0
    Y = axes[1]
    a2 = axes[0] * axes[0]
    b2 = axes[1] * axes[1]
    
    D = b2 - 2 * a2 * axes[1] + a2
    Yk = 0
    #sym_ox([X, Y], centre, color, canv)
    while Y >= Yk:
        if D < 0:
            D1 = 2 * D + (2 * Y - 1) * a2
            if D1 <= 0:
                X += 1
                D += (2 * X + 1) * b2
            else:
                X += 1
                Y -= 1
                D += (2 * X + 1) * b2 - (2 * Y - 1) * a2
        elif D == 0:
            X += 1
            Y -= 1
            D += (2 * X + 1) * b2 - (2 * Y - 1) * a2
        else:
            D2 = 2 * D - (2 * X + 1) * b2
            if D2 <= 0:
                X += 1
                Y -= 1
                D += (2 * X + 1) * b2 - (2 * Y - 1) * a2
            else:
                Y -= 1
                D += (-2 * Y + 1) * a2
        #sym_ox([X, Y], centre, color, canv)


def midpoint_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        #draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])
    a2 = axes[0] * axes[0]
    b2 = axes[1] * axes[1]
    
    x = 0
    y = axes[1]
    p = b2 - a2 * axes[1] + 0.25 * a2
    while x * b2 < y * a2:
        #sym_ox([x, y], centre, color, canv)
        if p >= 0:
            y -= 1
            p -= 2 * y * a2
        x += 1
        p += (2 * x + 1) * b2

    p += 0.75 * (a2 - b2) - (b2 * x + a2 * y)
    while y >= 0:
        #sym_ox([x, y], centre, color, canv)
        if p < 0:
            x += 1
            p += 2 * x * b2
        y -= 1
        p += (-2 * y + 1) * a2


def time_comp_ovals():
    data = [[i for i in range(50, 550, 50)]]
    funcs = [canonical_oval, parametric_oval, Brezenham_oval,
             midpoint_oval]

    eccentr = 1 - 25 ** 2 / 50 ** 2
    tmp = []
    for i in range(4):
        tmp.clear()
        for rad in data[0]:
            ax2 = round(np.sqrt(rad ** 2 * (1 - eccentr)))
            t0 = time.clock()
            for j in range(1000):
                funcs[i]((0, 0), [rad, ax2], '', '')
            t1 = time.clock() - t0
            tmp.append(t1 * 10)
        data.append(tmp[:])
    
    funcs = ['Каноническое ур-е',
             'Параметрическое ур-е',
             'Алгоритм Брезенхема',
             'Алгоритм средней точки']

    fig, ax = plt.subplots()

    ax.plot(data[0], data[1],
            data[0], data[2],
            data[0], data[3],
            data[0], data[4])

    plt.legend(funcs, loc=2)
    
    ax.set_ylabel('Время в мс')
    ax.set_xlabel('Большая полуость эллипса')
    ax.set_title('Временные характеристики алгоритмов')
    
    plt.show()
