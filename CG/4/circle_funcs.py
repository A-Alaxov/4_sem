import numpy as np


def rgb_to_hex(rgb):
    return "#%02x%02x%02x" % rgb


def set_intense(fill, alpha, back):
    fill = list(fill)
    for i in range(3):
        fill[i] = int(fill[i] * alpha + back[i] * (1 - alpha))
    return tuple(fill)


def draw_dot(dot, fill, canv):
    canv.create_line(dot[0], dot[1], dot[0] + 1, dot[1] + 1,\
                     fill = rgb_to_hex(fill))


def sym_oy(dot, centre, fill, canv):
    draw_dot(np.array(dot) + np.array(centre), fill, canv)
    draw_dot(np.array([dot[0], -dot[1]]) + np.array(centre), fill, canv)


def sym_ox(dot, centre, fill, canv):
    sym_oy(dot, centre, fill, canv)
    sym_oy([-dot[0], dot[1]], centre, fill, canv)


def sym_oct(dot, centre, fill, canv):
    sym_ox(dot, centre, fill, canv)
    sym_ox([dot[1], dot[0]], centre, fill, canv)


def lib_func(centre, rad, color, canv):
    canv.create_oval(centre[0] - rad, centre[1] - rad,
                     centre[0] + rad, centre[1] + rad,
                     outline = rgb_to_hex(color))


def canonical_eq(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return

    mid = int(round(rad / np.sqrt(2)))

    dot = [0, rad]
    sym_oct(dot, centre, color, canv)
    for x in range(mid + 1):
        dot[0] = x
        dot[1] = round(np.sqrt(rad * rad - x * x))
        sym_oct(dot, centre, color, canv)


def parametric_eq(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return

    dot = [rad, 0]
    count = int(round(np.pi / 4 * rad))
    t = 0
    sym_oct(dot, centre, color, canv)
    for i in range(count + 1):
        dot[0] = round(rad * np.cos(t))
        dot[1] = round(rad * np.sin(t))
        sym_oct(dot, centre, color, canv)
        t += 1 / rad


def Brezenham_method(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return

    X = 0
    Y = rad
    D = 2 * (1 - rad)
    Yk = rad / np.sqrt(2)
    sym_oct([X, Y], centre, color, canv)
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
        sym_oct([X, Y], centre, color, canv)


def midpoint_method(centre, rad, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(rad) != rad):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    rad = int(rad)
    
    if rad == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    x = 0
    y = rad
    p = 1.25 - rad
    while x <= y:
        sym_oct([x, y], centre, color, canv)
        if p >= 0:
            y -= 1
            p -= 2 * y
        x += 1
        p += 2 * x + 1
