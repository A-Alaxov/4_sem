import tkinter as tk
import tkinter.messagebox as msg
import tkinter.ttk as ttk
import numpy as np
from time_compare import time_compare
from stairs_research import stairs_research


def rotate_dot(dot, angle, centre):
    angle = np.radians(angle)
    return [round(centre[0] - (centre[0] - dot[0]) * np.cos(angle) -
            (dot[1] - centre[1]) * np.sin(angle)),
            round(centre[1] - (centre[0] - dot[0]) * np.sin(angle) +
            (dot[1] - centre[1]) * np.cos(angle))]


def rgb_to_hex(rgb):
    return "#%02x%02x%02x" % rgb


def set_intense(fill, alpha, back):
    fill = list(fill)
    for i in range(3):
        fill[i] = int(fill[i] * alpha + back[i] * (1 - alpha))
    return tuple(fill)


def draw_dot(dot, fill):
    canv.create_line(dot[0], dot[1], dot[0] + 1, dot[1] + 1,\
                     fill = rgb_to_hex(fill))


def draw_line(dot1, dot2, color):
    canv.create_line(dot1[0], dot1[1], dot2[0], dot2[1],
                     fill=color)
    canv.create_line(dot2[0], dot2[1], dot2[0] + 1, dot2[1] + 1,
                     fill=color)


def lib_func(beg, end, color, back):
    draw_line(beg, end, rgb_to_hex(color))


def cda_method(beg, end, color, back):
    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), fill = color)
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
        draw_dot((round(x), round(y)), fill = color)
        x += dx
        y += dy
        i += 1


def Brezenham_method(beg, end, color, back):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        msg.showerror('Ошибка', 'Для алгоритмов Брезенхема координаты должны \
быть целочисленными')
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return

    dx = int(np.fabs(end[0] - beg[0]))
    dy = int(np.fabs(end[1] - beg[1]))
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
        draw_dot((x, y), fill = color)
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


def integer_Brezenham_method(beg, end, color, back):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        msg.showerror('Ошибка', 'Для алгоритмов Брезенхема координаты должны \
быть целочисленными')
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return
    
    dx = int(np.fabs(end[0] - beg[0]))
    dy = int(np.fabs(end[1] - beg[1]))
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
        draw_dot((x, y), fill = color)
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
        

def Brezenham_method_without_stairs(beg, end, color, back):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        msg.showerror('Ошибка', 'Для алгоритмов Брезенхема координаты должны \
быть целочисленными')
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return
    
    dx = int(np.fabs(end[0] - beg[0]))
    dy = int(np.fabs(end[1] - beg[1]))
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

    new_color = set_intense(color, f, back)
    draw_dot((x, y), fill = new_color)
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
        new_color = set_intense(color, f, back)
        draw_dot((x, y), fill = new_color)
        i += 1


def Wu_method(beg, end, color, back):
    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), fill = color)
        return
    
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
        new_color = set_intense(color, 1 - intery % 1, back)
        draw_dot((x_draw, y_draw), fill = new_color)

        if change:
            x_draw += 1
        else:
            y_draw += 1
        new_color = set_intense(color, intery % 1, back)
        draw_dot((x_draw, y_draw), fill = new_color)
        intery += gradient
        x += 1


def draw_segment(entr1, entr2, func, color, back):
    string_1 = entr1.get()
    string_1 = " ".join(string_1.split())
    string_1.strip()

    if len(string_1) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введено начало отрезка")
    else:
        try:
            beg_dot = [float(i) for i in string_1.split(" ")]
                    
            if len(beg_dot) != 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: 44  10")
        else:
            string_2 = entr2.get()
            string_2 = " ".join(string_2.split())
            string_2.strip()
    
            if len(string_2) == 0:
                msg.showerror("Некорректный ввод",
                              "Не введён конец отрезка")
            else:
                try:
                    end_dot = [float(i) for i in string_2.split(" ")]
                            
                    if len(end_dot) != 2:
                        raise BaseException("Must be doubled")
                except:
                    msg.showerror("Некорректный ввод",
                                  "Введите координаты в правильной форме\n\
Например: 44  10")
                else:
                    back = tuple([int(i) for i in back.split(" ")])
                    color = tuple([int(i) for i in color.split(" ")])

                    canv.configure(bg = rgb_to_hex(back))
                    
                    if func == 1:
                        lib_func(beg_dot, end_dot, color, back)
                    elif func == 2:
                        cda_method(beg_dot, end_dot, color, back)
                    elif func == 3:
                        Brezenham_method(beg_dot, end_dot, color, back)
                    elif func == 4:
                        integer_Brezenham_method(beg_dot, end_dot, color, back)
                    elif func == 5:
                        Brezenham_method_without_stairs(beg_dot, end_dot,\
                                                        color, back)
                    elif func == 6:
                        Wu_method(beg_dot, end_dot, color, back)


def draw_circle(entr1, entr2, func, color, back):
    string_1 = entr1.get()
    string_1 = " ".join(string_1.split())
    string_1.strip()

    if len(string_1) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён угол поворота")
    else:
        try:
            angle = [float(i) for i in string_1.split(" ")]
                    
            if len(angle) != 1:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: 30")
        else:
            string_2 = entr2.get()
            string_2 = " ".join(string_2.split())
            string_2.strip()
    
            if len(string_2) == 0:
                msg.showerror("Некорректный ввод",
                              "Не введена длина отрезка")
            else:
                try:
                    leng = [float(i) for i in string_2.split(" ")]
                            
                    if len(leng) != 1:
                        raise BaseException("Must be doubled")
                except:
                    msg.showerror("Некорректный ввод",
                                  "Введите координаты в правильной форме\n\
Например: 100")
                else:
                    back = tuple([int(i) for i in back.split(" ")])
                    color = tuple([int(i) for i in color.split(" ")])

                    canv.configure(bg = rgb_to_hex(back))
                    
                    if func == 1:
                        func = lib_func
                    elif func == 2:
                        func = cda_method
                    elif func == 3:
                        func = Brezenham_method
                    elif func == 4:
                        func = integer_Brezenham_method
                    elif func == 5:
                        func = Brezenham_method_without_stairs
                    elif func == 6:
                        func = Wu_method

                    beg_dot = [300, 300]
                    rot_dot = [300 + leng[0], 300]
                    i = 0
                    while i < 360:
                        end_dot = rotate_dot(rot_dot, i, beg_dot)
                        func(beg_dot, end_dot, color, back)
                        i += angle[0]


def info():
    msg.showinfo("Информация", "Компьютерная графика №3\n\
Разработчик: Алахов Андрей, ИУ7-42б\n\n\
Эта программа позволяет выполняет отрисовку отрезков или спектров с помощью\
различных алгоритмов. Также доступны опции сравнения временных характеристик\
алгоритмов и исследования степенчатости выбранного алгоритма.\n\n\
Для задания координат введите их в следующем формате: X  Y")


def main_init(table_app, canv):
    info_text = "Введите координаты начала отрезка:"
    lbl1 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl1.grid(row = 10, column = 0)

    entr1 = tk.Entry(table_app, width=15, font="Arial 14")
    entr1.grid(row = 10, column = 1)
    entr1.insert(0, "0   0")

    info_text = "Введите координаты конца отрезка:"
    lbl2 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl2.grid(row = 11, column = 0)

    entr2 = tk.Entry(table_app, width=15, font="Arial 14")
    entr2.grid(row = 11, column = 1)
    entr2.insert(0, "483  401")
    canv.bind("<Button-3>", lambda event : add_dot(event, entr2))

    info_text = "Введите угол поворота (в градусах):"
    lbl3 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl3.grid(row = 12, column = 0)

    entr3 = tk.Entry(table_app, width=15, font="Arial 14")
    entr3.grid(row = 12, column = 1)
    entr3.insert(0, "30")

    info_text = "Введите длину отрезка:"
    lbl4 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl4.grid(row = 13, column = 0)

    entr4 = tk.Entry(table_app, width=15, font="Arial 14")
    entr4.grid(row = 13, column = 1)
    entr4.insert(0, "100")

    info_text = "Метод построения:"
    lbl5 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl5.grid(row = 0, column = 0, sticky=tk.W)

    info_text = "Цвет отрезка:"
    lbl6 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl6.grid(row = 0, column = 1, sticky=tk.W)

    info_text = "Цвет фона:"
    lbl7 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl7.grid(row = 0, column = 2, sticky=tk.W)

    var = tk.IntVar()
    names = [('Библиотечная ф-я', 1), ('Алгоритм ЦДА', 2),
             ('Алгоритм Брезенхема', 3),
             ('Целочисленный алгоритм Брезенхема', 4),
             ('Брезенхем с устранением ступенчатости', 5),
             ('Алгоритм Ву', 6)]
    row = 1
    for txt, func in names:
        tk.Radiobutton(table_app, text = txt, value = func, variable = var,\
                       font="Arial 14").grid(row=row, column = 0, sticky=tk.W)
        row += 1

    col_var = tk.StringVar()
    names = [('Белый', (255, 255, 255)), ('Чёрный', (0, 0, 0)),\
             ('Синий', (0, 0, 255)), ('Красный', (255, 0, 0)),\
             ('Зелёный', (0, 255, 0)), ('Оранжевый', (255, 140, 0)),\
             ('Пурпурный', (128, 0, 128))]
    row = 1
    for txt, col in names:
        tk.Radiobutton(table_app, text = txt, value = col, variable = col_var,\
                       font="Arial 14").grid(row=row, column = 1, sticky=tk.W)
        row += 1

    back_var = tk.StringVar()
    row = 1
    for txt, col in names:
        tk.Radiobutton(table_app, text = txt, value = col, variable = back_var,\
                       font="Arial 14").grid(row=row, column = 2, sticky=tk.W)
        row += 1

    btn1 = tk.Button(table_app, font="Arial 14",
                     text="Построить отрезок", bg = "#00FF00",
                     command=lambda : draw_segment(entr1, entr2, var.get(),\
                                                   col_var.get(),\
                                                   back_var.get()))
    btn1.grid(row = 10, column = 2, rowspan = 2, sticky = "nwes")
    btn2 = tk.Button(table_app, font="Arial 14",
                     text="Построить спектр", bg = "#00FF00",
                     command=lambda : draw_circle(entr3, entr4, var.get(),\
                                                  col_var.get(),\
                                                  back_var.get()))
    btn2.grid(row = 12, column = 2, rowspan = 2, sticky = "nwes")
    btn3 = tk.Button(table_app, font="Arial 14",
                     text="Очистить", bg = "pale green",
                     command=lambda : canv.delete("all"))
    btn3.grid(row = 14, column = 1, rowspan = 2, sticky = "nwes")
    btn4 = tk.Button(table_app, font="Arial 14",
                     text="Сравнить время работы", bg = "#00FF00",
                     command=lambda : time_compare())
    btn4.grid(row = 15, column = 0, sticky = tk.W + tk.E)
    btn5 = tk.Button(table_app, font="Arial 14",
                     text="Исследование ступенчатости", bg = "#00FF00",
                     command=lambda : stairs_research(var.get()))
    btn5.grid(row = 14, column = 0, sticky = tk.W + tk.E)
    btn6 = tk.Button(table_app, font="Arial 14",
                     text="Информация", bg = "dark sea green",
                     command=lambda : info())
    btn6.grid(row = 14, column = 2, rowspan = 2, sticky = "nwes")


if __name__ == "__main__":
    root = tk.Tk()
    app = tk.Frame(root)
    app.grid()
    root.title("Компьютерная графика №3")
    root.geometry((str(1500) + 'x' + str(600)))
    root.resizable(False, False)

    canv = tk.Canvas(root, width=600,
        height=600, bg="#ffffff")

    canv.grid(row = 0, column = 4, rowspan = 5)

    main_init(app, canv)

    root.mainloop()
