import numpy as np
from circle_funcs import rgb_to_hex, draw_dot, sym_oy, sym_ox


def lib_oval(centre, axes, color, canv):
    canv.create_oval(centre[0] - axes[0], centre[1] - axes[1],
                     centre[0] + axes[0], centre[1] + axes[1],
                     outline = rgb_to_hex(color))


def canonical_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])
    a2 = axes[0] * axes[0]
    b2 = axes[1] * axes[1]

    xfin = int(round(a2 / np.sqrt(a2 + b2)))
    yfir = int(round(b2 / np.sqrt(a2 + b2)))

    dot = [0, axes[1]]
    sym_ox(dot, centre, color, canv)
    for x in range(xfin):
        dot[0] = x
        dot[1] = round(np.sqrt(1 - x * x / a2) * axes[1])
        sym_ox(dot, centre, color, canv)

    for y in range(yfir + 1, -1, -1):
        dot[1] = y
        dot[0] = round(np.sqrt(1 - y * y / b2) * axes[0])
        sym_ox(dot, centre, color, canv)


def parametric_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])

    dot = [axes[0], 0]
    t = 0
    max_axis = max(axes)
    count = int(round(np.pi / 2 * max_axis))

    sym_ox(dot, centre, color, canv)
    for i in range(count + 1):
        dot[0] = round(axes[0] * np.cos(t))
        dot[1] = round(axes[1] * np.sin(t))
        sym_ox(dot, centre, color, canv)
        t += 1 / max_axis


def Brezenham_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])

    X = 0
    Y = axes[1]
    a2 = axes[0] * axes[0]
    b2 = axes[1] * axes[1]
    
    D = b2 - 2 * a2 * axes[1] + a2
    Yk = 0
    sym_ox([X, Y], centre, color, canv)
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
        sym_ox([X, Y], centre, color, canv)


def midpoint_oval(centre, axes, color, canv):
    if (int(centre[0]) != centre[0] or int(centre[1]) != centre[1]
        or int(axes[0]) != axes[0] or int(axes[1]) != axes[1]):
        
        msg.showerror('Ошибка', 'Координаты и радиус должны \
быть целочисленными')
        return
    
    if axes[0] == 0 and axes[1] == 0:
        draw_dot((round(centre[0]), round(centre[1])), color, canv)
        return
    
    axes[0] = int(axes[0])
    axes[1] = int(axes[1])
    a2 = axes[0] * axes[0]
    b2 = axes[1] * axes[1]
    
    x = 0
    y = axes[1]
    p = b2 - a2 * axes[1] + 0.25 * a2
    while x * b2 < y * a2:
        sym_ox([x, y], centre, color, canv)
        if p >= 0:
            y -= 1
            p -= 2 * y * a2
        x += 1
        p += (2 * x + 1) * b2

    p += 0.75 * (a2 - b2) - (b2 * x + a2 * y)
    while y >= 0:
        sym_ox([x, y], centre, color, canv)
        if p < 0:
            x += 1
            p += 2 * x * b2
        y -= 1
        p += (-2 * y + 1) * a2
