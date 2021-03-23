import tkinter as tk
import tkinter.messagebox as msg
import tkinter.ttk as ttk
import numpy as np
from PIL import Image, ImageTk


def get_middle(dot1, dot2):
    return ((dot1[0] + dot2[0]) / 2, (dot1[1] + dot2[1]) / 2)


def get_len(dot1, dot2):
    return np.sqrt((dot1[0] - dot2[0]) ** 2 +
                     (dot1[1] - dot2[1]) ** 2)


def rotate_dot(dot, angle, centre):
    angle = np.radians(angle)
    return [round(centre[0] - (centre[0] - dot[0]) * np.cos(angle) -
            (dot[1] - centre[1]) * np.sin(angle)),
            round(centre[1] - (centre[0] - dot[0]) * np.sin(angle) +
            (dot[1] - centre[1]) * np.cos(angle))]


def draw_dot(dot, color, canv):
    canv.create_line(
        dot[0],
        dot[1],
        dot[0] + 1,
        dot[1] + 1,
        fill=color
    )


images = []
def draw_cool_dot(dot, **kwargs):
    if 'alpha' in kwargs:
        alpha = int(kwargs.pop('alpha') * 255)
        fill = kwargs.pop('fill')
        fill = root.winfo_rgb(fill) + (alpha,)
        image = Image.new('RGBA', (1, 1), fill)
        images.append(ImageTk.PhotoImage(image))
        canv.create_image(dot[0], dot[1], image=images[-1], anchor='nw')


def draw_line(dot1, dot2, color):
    canv.create_line(dot1[0], dot1[1], dot2[0], dot2[1],
                     fill=color)


def find_angle(dot1, dot2):
    x = dot1[0] - dot2[0]
    y = dot2[1] - dot1[1]

    if x == 0:
        if y > 0:
            return 90
        else:
            return -90
        
    if x < 0:
        return np.degrees(np.arctan(y / x)) + 180
    
    return np.degrees(np.arctan(y / x))


def delete_all(dots1, dots2, tree1, tree2):
    dots1.clear()
    dots2.clear()
    tree1.delete(*tree1.get_children())
    tree2.delete(*tree2.get_children())

    try:
        canv_root.destroy()
    except:
        pass

    try:
        text_root.destroy()
    except:
        pass


def lib_func(beg, end, color):
    draw_line(beg, end, color)


def cda_method(beg, end, color):
    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), color, canv)
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
        draw_dot((round(x), round(y)), color, canv)
        x += dx
        y += dy
        i += 1


def Brezenham_method(beg, end, color):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), color, canv)
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
        draw_dot((x, y), color, canv)
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


def integer_Brezenham_method(beg, end, color):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), color, canv)
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
        draw_dot((x, y), color, canv)
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
        

def Brezenham_method_without_stairs(beg, end, color):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return

    if beg[0] == end[0] and beg[1] == end[1]:
        draw_dot((round(beg[0]), round(beg[1])), color, canv)
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

    draw_cool_dot((x, y), fill = color, alpha = f)
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
        draw_cool_dot((x, y), fill = color, alpha = f)
        i += 1


def Wu_method(beg, end, color):
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
        draw_cool_dot((x_draw, y_draw), fill = color, alpha = 1 - intery % 1)

        if change:
            x_draw += 1
        else:
            y_draw += 1
        draw_cool_dot((x_draw, y_draw), fill = color, alpha = intery % 1)
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
                    canv.configure(bg = back)
                    
                    if func == 1:
                        lib_func(beg_dot, end_dot, color)
                    elif func == 2:
                        cda_method(beg_dot, end_dot, color)
                    elif func == 3:
                        Brezenham_method(beg_dot, end_dot, color)
                    elif func == 4:
                        integer_Brezenham_method(beg_dot, end_dot, color)
                    elif func == 5:
                        Brezenham_method_without_stairs(beg_dot, end_dot, color)
                    elif func == 6:
                        Wu_method(beg_dot, end_dot, color)


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
                    canv.configure(bg = back)
                    
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
                        func(beg_dot, end_dot, color)
                        i += angle[0]
                    


def add_dot(event, entr2):
    x = (event.x - 100) * real_width / (screen_width - 200) + min_x
    y = max_y - (event.y - 100) * real_height / (screen_height - 200)

    entr2.delete(0, tk.END)
    entr2.insert(0, "{:.2f} {:.2f}".format(x, y))


def info():
    msg.showinfo("Информация", "Компьютерная графика #2\n\
Разработчик: Алахов Андрей, ИУ7-42б\n\n\
Эта программа позволяет осуществить перенос, поворот и масштабирование \
исходного рисунка. Также доступны опции возврата к исходному и предыдущему \
рисункам.\n\n\
Для задания величин смещения введите их в следующем формате: X  Y\n\
Для задания центра масштабирования и поворота введите его координаты в \
следующем формате: X  Y\n\
Для задания коэффициентов масштабирования введите их в следующем формате: kx  \
ky\n\
Для задания центра масштабирования и поворота можно сделать клик ПКМ на холст \
в нужной точке\n\n\
На рисунке для удобства отображены координаты центральной точки")


def main_init(table_app, canv):
    info_text = "Введите координаты начала отрезка:"
    lbl1 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl1.grid(row = 0, column = 0, columnspan = 2)

    entr1 = tk.Entry(table_app, width=15, font="Arial 14")
    entr1.grid(row = 0, column = 2)
    entr1.insert(0, "0   0")

    info_text = "Введите координаты конца отрезка:"
    lbl2 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl2.grid(row = 1, column = 0, columnspan = 2)

    entr2 = tk.Entry(table_app, width=15, font="Arial 14")
    entr2.grid(row = 1, column = 2)
    entr2.insert(0, "483  401")
    canv.bind("<Button-3>", lambda event : add_dot(event, entr2))

    info_text = "Введите угол поворота (в градусах):"
    lbl3 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl3.grid(row = 2, column = 0, columnspan = 2)

    entr3 = tk.Entry(table_app, width=15, font="Arial 14")
    entr3.grid(row = 2, column = 2)
    entr3.insert(0, "30")

    info_text = "Введите длину отрезка:"
    lbl4 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl4.grid(row = 3, column = 0, columnspan = 2)

    entr4 = tk.Entry(table_app, width=15, font="Arial 14")
    entr4.grid(row = 3, column = 2)
    entr4.insert(0, "100")

    var = tk.IntVar()
    names = [('Библиотечная ф-я', 1), ('Алгоритм ЦДА', 2),
             ('Алгоритм Брезенхема', 3),
             ('Целочисленный алгоритм Брезенхема', 4),
             ('Брезенхем с устранением ступенчатости', 5),
             ('Алгоритм Ву', 6)]
    row = 7
    for txt, func in names:
        tk.Radiobutton(table_app, text = txt, value = func, variable = var, font="Arial 14")\
        .grid(row=row, column = 0, sticky=tk.W)
        row += 1

    col_var = tk.StringVar()
    names = [('Белый', 'white'), ('Чёрный', 'black'), ('Синий', 'blue'),
             ('Красный', 'red'), ('Зелёный', 'green'),
             ('Оранжевый', 'dark orange'), ('Пурпурный', 'purple')]
    row = 7
    for txt, col in names:
        tk.Radiobutton(table_app, text = txt, value = col, variable = col_var, font="Arial 14")\
        .grid(row=row, column = 1, sticky=tk.W)
        row += 1

    back_var = tk.StringVar()
    row = 7
    for txt, col in names:
        tk.Radiobutton(table_app, text = txt, value = col, variable = back_var, font="Arial 14")\
        .grid(row=row, column = 2, sticky=tk.W)
        row += 1

    btn1 = tk.Button(table_app, font="Arial 14", text="Библиотечная ф-я",
                     bg="#00FFFF",
                     command=lambda : draw_segment(entr1, entr2, lib_func))
    btn1.grid(row = 4, column = 0, sticky = tk.W + tk.E)
    
    btn2 = tk.Button(table_app, font="Arial 14", text="Алгоритм ЦДА",
                     bg="#00FFFF",
                     command=lambda : draw_segment(entr1, entr2, cda_method))
    btn2.grid(row = 4, column = 1, sticky = tk.W + tk.E)

    btn3 = tk.Button(table_app, font="Arial 14", text="Алгоритм Брезенхема",
                     bg="#00FFFF",
                     command=lambda : draw_segment(entr1, entr2, Brezenham_method))
    btn3.grid(row = 4, column = 2, sticky = tk.W + tk.E)

    btn8 = tk.Button(table_app, font="Arial 14",
                     text="Алгоритм Брезенхема с устранением ступенчатости", bg="#00FF00",
                     command=lambda : draw_segment(entr1, entr2, Brezenham_method_without_stairs))
    btn8.grid(row = 6, column = 0, columnspan = 3, sticky = tk.W + tk.E)
    
    btn9 = tk.Button(table_app, font="Arial 14",
                     text="Алгоритм Ву", bg = "#00FF00",
                     command=lambda : draw_segment(entr1, entr2, Wu_method))
    btn9.grid(row = 5, column = 0, sticky = tk.W + tk.E)

    btn10 = tk.Button(table_app, font="Arial 14",
                     text="Построить отрезок", bg = "#00FF00",
                     command=lambda : draw_segment(entr1, entr2, var.get(), col_var.get(), back_var.get()))
    btn10.grid(row = 15, column = 0, sticky = tk.W + tk.E)
    btn11 = tk.Button(table_app, font="Arial 14",
                     text="Построить спектр", bg = "#00FF00",
                     command=lambda : draw_circle(entr3, entr4, var.get(), col_var.get(), back_var.get()))
    btn11.grid(row = 15, column = 1, sticky = tk.W + tk.E)


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
