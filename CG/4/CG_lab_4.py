import tkinter as tk
import tkinter.messagebox as msg
import tkinter.ttk as ttk
import numpy as np
from time_compare import time_compare, time_comp_ovals
from oval_funcs import *
from circle_funcs import *
        
            
def draw_circle(entr1, entr2, func, color, back):
    string_1 = entr1.get()
    string_1 = " ".join(string_1.split())
    string_1.strip()

    if len(string_1) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён центр окружности")
    else:
        try:
            centre = [float(i) for i in string_1.split(" ")]
                    
            if len(centre) != 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: 300  300")
        else:
            string_2 = entr2.get()
            string_2 = " ".join(string_2.split())
            string_2.strip()
    
            if len(string_2) == 0:
                msg.showerror("Некорректный ввод",
                              "Не введён радиус окружности")
            else:
                try:
                    rad = [float(i) for i in string_2.split(" ")]
                            
                    if len(rad) != 1:
                        raise BaseException("Must be doubled")
                except:
                    msg.showerror("Некорректный ввод",
                                  "Введите радиус в правильной форме\n\
Например: 200")
                else:
                    back = tuple([int(i) for i in back.split(" ")])
                    color = tuple([int(i) for i in color.split(" ")])

                    canv.configure(bg = rgb_to_hex(back))
                    
                    if func == 1:
                        canonical_eq(centre, rad[0], color, canv)
                    elif func == 2:
                        parametric_eq(centre, rad[0], color, canv)
                    elif func == 3:
                        Brezenham_method(centre, rad[0], color, canv)
                    elif func == 4:
                        midpoint_method(centre, rad[0], color, canv)
                    elif func == 5:
                        lib_func(centre, rad[0], color, canv)


def draw_ellipse(entr1, entr2, func, color, back):
    string_1 = entr1.get()
    string_1 = " ".join(string_1.split())
    string_1.strip()

    if len(string_1) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён центр эллипса")
    else:
        try:
            centre = [float(i) for i in string_1.split(" ")]
                    
            if len(centre) != 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: 300  300")
        else:
            string_2 = entr2.get()
            string_2 = " ".join(string_2.split())
            string_2.strip()
    
            if len(string_2) == 0:
                msg.showerror("Некорректный ввод",
                              "Не введены полуоси")
            else:
                try:
                    koefs = [float(i) for i in string_2.split(" ")]
                            
                    if len(koefs) != 2:
                        raise BaseException("Must be doubled")
                except:
                    msg.showerror("Некорректный ввод",
                                  "Введите полуоси в правильной форме\n\
Например: 300  100")
                else:
                    back = tuple([int(i) for i in back.split(" ")])
                    color = tuple([int(i) for i in color.split(" ")])

                    canv.configure(bg = rgb_to_hex(back))
                    
                    if func == 1:
                        canonical_oval(centre, koefs, color, canv)
                    elif func == 2:
                        parametric_oval(centre, koefs, color, canv)
                    elif func == 3:
                        Brezenham_oval(centre, koefs, color, canv)
                    elif func == 4:
                        midpoint_oval(centre, koefs, color, canv)
                    elif func == 5:
                        lib_oval(centre, koefs, color, canv)


def draw_conc_circles(entr1, entr2, entr3, entr4, func, color, back):
    string = entr1.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён центр окружностей")
        return
    try:
        centre = [float(i) for i in string.split(" ")]
                
        if len(centre) != 2:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите координаты в правильной форме\n\
Например: 300  300")
        return
    
    string = entr2.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён радиус начальной окружности")
        return
    try:
        rad = [float(i) for i in string.split(" ")]
                
        if len(rad) != 1:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите радиус в правильной форме\n\
Например: 30")
        return
    rad = rad[0]

    string = entr3.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён шаг изменения радиуса")
        return
    try:
        step = [float(i) for i in string.split(" ")]
                
        if len(step) != 1 or int(step[0]) != step[0]:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите шаг изменения радиуса в правильной форме\n\
Например: 20")
        return
    step = step[0]

    string = entr4.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введено количество окружностей")
        return
    try:
        count = [float(i) for i in string.split(" ")]
                
        if len(count) != 1 or int(count[0]) != count[0]:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите количество окружностей в правильной форме\n\
Например: 10")
        return
    count = int(count[0])
    
    back = tuple([int(i) for i in back.split(" ")])
    color = tuple([int(i) for i in color.split(" ")])

    canv.configure(bg = rgb_to_hex(back))
    
    if func == 1:
        func = canonical_eq
    elif func == 2:
        func = parametric_eq
    elif func == 3:
        func = Brezenham_method
    elif func == 4:
        func = midpoint_method
    elif func == 5:
        func = lib_func

    for i in range(count):
        func(centre, rad, color, canv)
        rad += step


def draw_conc_ovals(entr1, entr2, entr3, entr4, func, color, back):
    string = entr1.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён центр эллипсов")
        return
    try:
        centre = [float(i) for i in string.split(" ")]
                
        if len(centre) != 2:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите координаты в правильной форме\n\
Например: 300  300")
        return
    
    string = entr2.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введены полуоси начального эллипса")
        return
    try:
        coefs = [float(i) for i in string.split(" ")]
                
        if len(coefs) != 2:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите полуоси в правильной форме\n\
Например: 25 10")
        return

    string = entr3.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён шаг изменения полуоси Х")
        return
    try:
        step = [float(i) for i in string.split(" ")]
                
        if len(step) != 1 or int(step[0]) != step[0]:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите шаг изменения полуоси Х в правильной форме\n\
Например: 25")
        return
    step = int(step[0])

    string = entr4.get()
    string = " ".join(string.split())
    string.strip()
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введено количество эллипсов")
        return
    try:
        count = [float(i) for i in string.split(" ")]
                
        if len(count) != 1 or int(count[0]) != count[0]:
            raise BaseException("Must be doubled")
    except:
        msg.showerror("Некорректный ввод",
                      "Введите количество эллипсов в правильной форме\n\
Например: 10")
        return
    count = int(count[0])
    
    back = tuple([int(i) for i in back.split(" ")])
    color = tuple([int(i) for i in color.split(" ")])

    canv.configure(bg = rgb_to_hex(back))
    
    if func == 1:
        func = canonical_oval
    elif func == 2:
        func = parametric_oval
    elif func == 3:
        func = Brezenham_oval
    elif func == 4:
        func = midpoint_oval
    elif func == 5:
        func = lib_oval

    eccentr = 1 - min(coefs) ** 2 / max(coefs) ** 2
    for i in range(count):
        func(centre, coefs, color, canv)
        coefs[0] += step
        if coefs[1] > coefs[0]:
            coefs[1] = round(np.sqrt(coefs[0] * coefs[0] / (1 - eccentr)))
        else:
            coefs[1] = round(np.sqrt(coefs[0] * coefs[0] * (1 - eccentr)))


def info():
    msg.showinfo("Информация", "Компьютерная графика №4\n\
Разработчик: Алахов Андрей, ИУ7-42б\n\n\
Эта программа выполняет отрисовку окружностей или эллипсов с помощью \
различных алгоритмов.\nТакже доступны опции построения концентрических \
окружностей эллипсов и сравнения временных характеристик алгоритмов.")


def main_init(table_app, canv):
    #Окружности
    info_text = "Координаты центра окружности:"
    lbl1 = tk.Label(table_app, text=info_text, font="12")
    lbl1.grid(row = 10, column = 0)

    entr1 = tk.Entry(table_app, width=15, font="12")
    entr1.grid(row = 10, column = 1)
    entr1.insert(0, "300  300")

    info_text = "Радиус окружности:"
    lbl2 = tk.Label(table_app, text=info_text, font="12")
    lbl2.grid(row = 11, column = 0)

    entr2 = tk.Entry(table_app, width=15, font="12")
    entr2.grid(row = 11, column = 1)
    entr2.insert(0, "200")

    #Эллипсы
    info_text = ""
    fant3 = tk.Label(table_app, text=info_text, font="12")
    fant3.grid(row = 12, column = 0)
    
    info_text = "Координаты центра эллипса:"
    lbl3 = tk.Label(table_app, text=info_text, font="12")
    lbl3.grid(row = 13, column = 0)

    entr3 = tk.Entry(table_app, width=15, font="12")
    entr3.grid(row = 13, column = 1)
    entr3.insert(0, "300  300")

    info_text = "Полуоси эллипса:"
    lbl4 = tk.Label(table_app, text=info_text, font="12")
    lbl4.grid(row = 14, column = 0)

    entr4 = tk.Entry(table_app, width=15, font="12")
    entr4.grid(row = 14, column = 1)
    entr4.insert(0, "250  50")

    #Концентрические окружности
    info_text = ""
    fant1 = tk.Label(table_app, text=info_text, font="12")
    fant1.grid(row = 15, column = 0)
    
    info_text = "Координаты центра окружности:"
    lbl5 = tk.Label(table_app, text=info_text, font="12")
    lbl5.grid(row = 16, column = 0)

    entr5 = tk.Entry(table_app, width=15, font="12")
    entr5.grid(row = 16, column = 1, sticky=tk.S)
    entr5.insert(0, "300  300")

    info_text = "Радиус начальной окружности:"
    lbl6 = tk.Label(table_app, text=info_text, font="12")
    lbl6.grid(row = 17, column = 0)

    entr6 = tk.Entry(table_app, width=15, font="12")
    entr6.grid(row = 17, column = 1)
    entr6.insert(0, "30")

    info_text = "Шаг изменения радиуса:"
    lbl7 = tk.Label(table_app, text=info_text, font="12")
    lbl7.grid(row = 18, column = 0)

    entr7 = tk.Entry(table_app, width=15, font="12")
    entr7.grid(row = 18, column = 1)
    entr7.insert(0, "20")

    info_text = "Количество окружностей:"
    lbl8 = tk.Label(table_app, text=info_text, font="12")
    lbl8.grid(row = 19, column = 0)

    entr8 = tk.Entry(table_app, width=15, font="12")
    entr8.grid(row = 19, column = 1)
    entr8.insert(0, "10")

    #Концентрические эллипсы
    info_text = ""
    fant2 = tk.Label(table_app, text=info_text, font="12")
    fant2.grid(row = 20, column = 0)
    
    info_text = "Координаты центра эллипса:"
    lbl9 = tk.Label(table_app, text=info_text, font="12")
    lbl9.grid(row = 21, column = 0)

    entr9 = tk.Entry(table_app, width=15, font="12")
    entr9.grid(row = 21, column = 1, sticky=tk.S)
    entr9.insert(0, "300  300")

    info_text = "Полуоси начального эллипса:"
    lbl10 = tk.Label(table_app, text=info_text, font="12")
    lbl10.grid(row = 22, column = 0)

    entr10 = tk.Entry(table_app, width=15, font="12")
    entr10.grid(row = 22, column = 1)
    entr10.insert(0, "25 10")

    info_text = "Шаги изменения полуоси Х:"
    lbl11 = tk.Label(table_app, text=info_text, font="12")
    lbl11.grid(row = 23, column = 0)

    entr11 = tk.Entry(table_app, width=15, font="12")
    entr11.grid(row = 23, column = 1)
    entr11.insert(0, "25")

    info_text = "Количество эллипсов:"
    lbl12 = tk.Label(table_app, text=info_text, font="12")
    lbl12.grid(row = 24, column = 0)

    entr12 = tk.Entry(table_app, width=15, font="12")
    entr12.grid(row = 24, column = 1)
    entr12.insert(0, "10")
    
    #Выборы
    info_text = "Метод построения:"
    lbl5 = tk.Label(table_app, text=info_text, font="12")
    lbl5.grid(row = 0, column = 0, sticky=tk.W)

    info_text = "Цвет отрезка:"
    lbl6 = tk.Label(table_app, text=info_text, font="12")
    lbl6.grid(row = 0, column = 1, sticky=tk.W)

    info_text = "Цвет фона:"
    lbl7 = tk.Label(table_app, text=info_text, font="12")
    lbl7.grid(row = 0, column = 2, sticky=tk.W)

    var = tk.IntVar()
    names = [('Каноническое ур-е', 1), ('Параметрическое ур-е', 2),
             ('Алгоритм Брезенхема', 3), ('Алгоритм средней точки', 4),
             ('Библиотечная ф-я', 5)]
    row = 1
    for txt, func in names:
        tk.Radiobutton(table_app, text = txt, value = func, variable = var,
                       font="12").grid(row=row, column = 0, sticky=tk.W)
        row += 1

    col_var = tk.StringVar()
    names = [('Белый', (255, 255, 255)), ('Чёрный', (0, 0, 0)),\
             ('Синий', (0, 0, 255)), ('Красный', (255, 0, 0)),\
             ('Зелёный', (0, 255, 0)), ('Пурпурный', (128, 0, 128))]
    row = 1
    for txt, col in names:
        tk.Radiobutton(table_app, text = txt, value = col, variable = col_var,
                       font="12").grid(row=row, column = 1, sticky=tk.W)
        row += 1

    back_var = tk.StringVar()
    row = 1
    for txt, col in names:
        tk.Radiobutton(table_app, text = txt, value = col, variable = back_var,
                       font="12").grid(row=row, column = 2, sticky=tk.W)
        row += 1

    #Единичные
    btn1 = tk.Button(table_app, font="12",
                     text="Построить\nокружность", bg = "#00FF00",
                     command=lambda : draw_circle(entr1, entr2, var.get(),
                                                  col_var.get(),
                                                  back_var.get()))
    btn1.grid(row = 10, column = 2, rowspan = 2, sticky = "nwes")
    btn2 = tk.Button(table_app, font="12",
                     text="Построить\nэллипс", bg = "#00FF00",
                     command=lambda : draw_ellipse(entr3, entr4, var.get(),
                                                col_var.get(), back_var.get()))
    btn2.grid(row = 13, column = 2, rowspan = 2, sticky = "nwes")
    
    #Концентрические
    btn1 = tk.Button(table_app, font="12",
                     text="Построить\nконцентрические\nокружности",
                     bg = "#00FF00",
                     command=lambda : draw_conc_circles(entr5, entr6, entr7,
                                                        entr8, var.get(),
                                                        col_var.get(),
                                                        back_var.get()))
    btn1.grid(row = 16, column = 2, rowspan = 4, sticky = "nwes")
    btn2 = tk.Button(table_app, font="12",
                     text="Построить\nконцентрические\nэллипсы", bg = "#00FF00",
                     command=lambda : draw_conc_ovals(entr9, entr10, entr11,
                                                      entr12, var.get(),
                                                      col_var.get(),
                                                      back_var.get()))
    btn2.grid(row = 21, column = 2, rowspan = 4, sticky = "nwes")
    
    #Прочее
    btn3 = tk.Button(table_app, font="Arial 12",
                     text="Очистить", bg = "pale green",
                     command=lambda : canv.delete("all"))
    btn3.grid(row = 26, column = 1, rowspan = 2, sticky = "nwes")
    btn4 = tk.Button(table_app, font="Arial 12",
                     text="Сравнить время построения окружностей",
                     bg = "#00FF00", command=lambda : time_compare())
    btn4.grid(row = 26, column = 0, sticky = tk.W + tk.E)
    btn5 = tk.Button(table_app, font="Arial 12",
                     text="Сравнить время построения эллипсов",
                     bg = "#00FF00", command=lambda : time_comp_ovals())
    btn5.grid(row = 27, column = 0, sticky = tk.W + tk.E)
    btn6 = tk.Button(table_app, font="Arial 12",
                     text="Информация", bg = "dark sea green",
                     command=lambda : info())
    btn6.grid(row = 26, column = 2, rowspan = 2, sticky = "nwes")


if __name__ == "__main__":
    root = tk.Tk()
    app = tk.Frame(root)
    app.grid()
    root.title("Компьютерная графика №4")
    root.geometry((str(1200) + 'x' + str(630)))
    root.resizable(False, False)

    global canv
    canv = tk.Canvas(root, width=600,
        height=600, bg="#ffffff")

    canv.grid(row = 0, column = 4)

    main_init(app, canv)

    root.mainloop()
