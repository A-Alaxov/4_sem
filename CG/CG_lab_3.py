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
    return (centre[0] - (centre[0] - dot[0]) * np.cos(angle) -
            (dot[1] - centre[1]) * np.sin(angle),
            centre[1] - (centre[0] - dot[0]) * np.sin(angle) +
            (dot[1] - centre[1]) * np.cos(angle))


def draw_dot(dot, color, canv):
    canv.create_line(
        dot[0],
        dot[1],
        dot[0] + 1,
        dot[1],
        fill=color,
        tags=["dot", "for_delete"]
    )


def draw_cool_dot(dot, canv, **kwargs):
    if 'alpha' in kwargs:
        alpha = int(kwargs.pop('alpha') * 255)
        fill = kwargs.pop('fill')
        fill = root.winfo_rgb(fill) + (alpha,)
        image = ImageTk.PhotoImage(Image.new('RGBA', (1, 1), fill))
        canv.create_image(dot[0], dot[1], image=image, anchor='nw')
    
    canv.create_line(
        dot[0],
        dot[1],
        dot[0] + 1,
        dot[1],
        **kwargs
    )


def draw_line(dot1, dot2, canv):
    canv.create_line(dot1[0], dot1[1], dot2[0], dot2[1],
                     fill="blue", tags=["line", "for_delete"])


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


def lib_func(beg, end):
    draw_line(beg, end, canv)


def cda_method(beg, end):
    if np.fabs(end[0] - beg[0]) >= np.fabs(end[1] - beg[1]):
        len = np.fabs(end[0] - beg[0])
    else:
        len = np.fabs(end[1] - beg[1])

    dx = (end[0] - beg[0]) / len
    dy = (end[1] - beg[1]) / len

    x = beg[0] + 0.5 * np.sign(dx)
    y = beg[1] + 0.5 * np.sign(dy)

    i = 1
    while i <= len:
        draw_cool_dot((int(x), int(y)), canv, fill = "green", alpha = 0.5)
        draw_dot((int(x), int(y)), "green", canv)
        x += dx
        y += dy
        i += 1


def Brezenham_method(beg, end):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return
    
    x = beg[0]
    y = beg[1]
    dx = np.fabs(end[0] - beg[0])
    dy = np.fabs(end[1] - beg[1])
    s1 = np.sign(end[0] - beg[0])
    s2 = np.sign(end[1] - beg[1])
    
    if dy > dx:
        dx, dy = dy, dx
        change = 1
    else:
        change = 0

    e = dy / dx - 0.5

    for i in range(int(dx)):
        draw_dot((x, y), "red", canv)
        while e >= 0:
            if change:
                x += s1
            else:
                y += s2
            e -= 1
        if change:
            y += s2
        else:
            x += s1
        e += (dy / dx)


def integer_Brezenham_method(beg, end):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return
    
    x = beg[0]
    y = beg[1]
    dx = np.fabs(end[0] - beg[0])
    dy = np.fabs(end[1] - beg[1])
    s1 = np.sign(end[0] - beg[0])
    s2 = np.sign(end[1] - beg[1])
    
    if dy > dx:
        dx, dy = dy, dx
        change = 1
    else:
        change = 0

    e = 2 * dy - dx

    for i in range(int(dx)):
        draw_dot((x, y), "dark orange", canv)
        while e >= 0:
            if change:
                x += s1
            else:
                y += s2
            e -= (2 * dx)
        if change:
            y += s2
        else:
            x += s1
        e += (2 * dy)
        draw_cool_dot((int(x), int(y)), canv, fill = "green", alpha = 0.5)


def Brezenham_method_without_stairs(beg, end):
    if (int(beg[0]) != beg[0] or int(beg[1]) != beg[1] or
        int(end[0]) != end[0] or int(end[1]) != end[1]):
        
        print("Not integer")
        return
    
    x = beg[0]
    y = beg[1]
    dx = np.fabs(end[0] - beg[0])
    dy = np.fabs(end[1] - beg[1])
    s1 = np.sign(end[0] - beg[0])
    s2 = np.sign(end[1] - beg[1])
    
    if dy > dx:
        dx, dy = dy, dx
        change = 1
    else:
        change = 0

    e = 2 * dy - dx

    for i in range(int(dx)):
        draw_dot((x, y), "dark orange", canv)
        while e >= 0:
            if change:
                x += s1
            else:
                y += s2
            e -= (2 * dx)
        if change:
            y += s2
        else:
            x += s1
        e += (2 * dy)


def draw_segment(entr1, entr2, func):
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
                    func(beg_dot, end_dot)


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
    lbl1.grid(row = 0, column = 0, columnspan = 3)

    entr1 = tk.Entry(table_app, width=15, font="Arial 14")
    entr1.grid(row = 0, column = 3)
    entr1.insert(0, "483  401")

    info_text = "Введите координаты конца отрезка:"
    lbl2 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl2.grid(row = 1, column = 0, columnspan = 3)

    entr2 = tk.Entry(table_app, width=15, font="Arial 14")
    entr2.grid(row = 1, column = 3)
    entr2.insert(0, "0   0")
    canv.bind("<Button-3>", lambda event : add_dot(event, entr2))

    info_text = "Введите угол поворота (в градусах):"
    lbl3 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl3.grid(row = 2, column = 0, columnspan = 3)

    entr3 = tk.Entry(table_app, width=15, font="Arial 14")
    entr3.grid(row = 2, column = 3)
    entr3.insert(0, "-45")

    info_text = "Введите коэффиценты масштабирования по X и Y:"
    lbl4 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl4.grid(row = 3, column = 0, columnspan = 3)

    entr4 = tk.Entry(table_app, width=15, font="Arial 14")
    entr4.grid(row = 3, column = 3)
    entr4.insert(0, "1.5 3")

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

    btn7 = tk.Button(table_app, font="Arial 14", text="Целочисленный алгоритм Брезенхема",
                     command=lambda : draw_segment(entr1, entr2, integer_Brezenham_method))
    btn7.grid(row = 4, column = 3, rowspan = 2,
              sticky = tk.W + tk.E + tk.N + tk.S)

    btn8 = tk.Button(table_app, font="Arial 14",
                     text="Вывести исходное изображение", bg="#00FF00",
                     command=lambda : go_to_default(figure, default_figure, moves))
    btn8.grid(row = 5, column = 1, columnspan = 2, sticky = tk.W + tk.E)
    
    btn9 = tk.Button(table_app, font="Arial 14", text="Шаг назад",
                     bg = "#00FF00",
                     command=lambda : move_back(figure, moves))
    btn9.grid(row = 5, column = 0, sticky = tk.W + tk.E)


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
