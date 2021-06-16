import tkinter as tk
import tkinter.messagebox as msg
import tkinter.ttk as ttk
import numpy as np


screen_width, screen_height = 800, 800
real_width, real_height = 600, 600
min_x, max_y = -300, 300


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


def shift_dot(dot, x, y):
    return (dot[0] + x, dot[1] + y)


def scale_dot(dot, kx, ky, centre):
    dx = kx * (dot[0] - centre[0])
    dy = ky * (dot[1] - centre[1])
    return (centre[0] + dx, centre[1] + dy)


def change_coords(dot):
    return ((dot[0] - min_x) * (screen_width - 200) / real_width + 100,
            (max_y - dot[1]) * (screen_height - 200) / real_height + 100)


def draw_dot(dot, color, canv):
    dot_for_screen = change_coords(dot)
    
    canv.create_oval(
        dot_for_screen[0] - 5,
        dot_for_screen[1] - 5,
        dot_for_screen[0] + 5,
        dot_for_screen[1] + 5,
        fill=color,
        outline="#000000",
        tags=["dot", "for_delete"],
    )
    
    canv.create_text(
        dot_for_screen[0], dot_for_screen[1] + 15,
        text="({:.2f}; {:.2f})".format(dot[0], dot[1]),
        font="Arial 14", tags=["for_delete"]
    )


def draw_line(dot1, dot2, canv):
    canv.create_line(dot1[0], dot1[1], dot2[0], dot2[1],
                     fill="#00FFFF", tags=["line", "for_delete"], width=2)


def get_circle(centre, r, half):
    arc = []
    num = 60
    
    step = r / num
    if half == "full":
        step *= 2

    start1 = -r
    start2 = r
    if half == "right":
        start1 = 0
    if half == "left":
        start2 = 0

    for i in range(num + 1):
        x = start1 + step * i
        y = np.sqrt((1 - (x ** 2) / (r ** 2)) * r ** 2)
        arc.append((x + centre[0], y + centre[1]))
    for i in range(num + 1):
        x = start2 - step * i
        y = -np.sqrt((1 - (x ** 2) / (r ** 2)) * r ** 2)
        arc.append((x + centre[0], y + centre[1]))

    return arc


def create_axis(canv, zero_dot):
    canv.create_line(zero_dot[0], 0, zero_dot[0], screen_height)
    canv.create_line(0, zero_dot[1], screen_width, zero_dot[1])
    
    canv.create_line(zero_dot[0] - 1, 3, zero_dot[0] - 10, 12)
    canv.create_line(zero_dot[0], 3, zero_dot[0] + 9, 12)
    canv.create_text(zero_dot[0] - 15, 12, text="Y", font="Arial 12")
    
    canv.create_line(screen_width - 3, zero_dot[1], screen_width - 12,
                     zero_dot[1] - 9)
    canv.create_line(screen_width - 3, zero_dot[1], screen_width - 12,
                     zero_dot[1] + 9)
    canv.create_text(screen_width - 10, zero_dot[1] + 20, text="X",
                     font="Arial 12")
    
    canv.create_text(zero_dot[0] - 10, zero_dot[1] - 12, text="0",
                     font="Arial 12")
    
    canv.create_line(zero_dot[0] + 40, zero_dot[1] - 10, zero_dot[0] + 40,
                     zero_dot[1] + 10)
    canv.create_text(
        zero_dot[0] + 40, zero_dot[1] - 20,
        text="{:.2f}".format(40 * real_width / (screen_width - 200)),
        font="Arial 12")
    
    canv.create_line(zero_dot[0] - 10, zero_dot[1] - 40, zero_dot[0] + 10,
                     zero_dot[1] - 40)
    canv.create_text(
        zero_dot[0] - 30, zero_dot[1] - 40,
        text="{:.2f}".format(40 * real_height / (screen_height - 200)),
        font="Arial 12")


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


def draw_figure(figure, canv):
    draw_line(figure[0], figure[1], canv)
    draw_line(figure[1], figure[2], canv)
    draw_line(figure[2], figure[3], canv)
    draw_line(figure[3], figure[0], canv)

    rhomb0 = get_middle(figure[0], figure[1])
    rhomb1 = get_middle(figure[1], figure[2])
    rhomb2 = get_middle(figure[2], figure[3])
    rhomb3 = get_middle(figure[3], figure[0])
    
    draw_line(rhomb0, rhomb1, canv)
    draw_line(rhomb1, rhomb2, canv)
    draw_line(rhomb2, rhomb3, canv)
    draw_line(rhomb3, rhomb0, canv)

    centre = get_middle(rhomb0, rhomb2)
    up_dot = get_middle(centre, rhomb0)
    down_dot = get_middle(centre, rhomb2)
    
    x_radius = get_len(rhomb1, centre) / 2
    y_radius = get_len(rhomb0, centre)

    draw_line(up_dot, down_dot, canv)
    draw_line(get_middle(get_middle(rhomb3, centre), centre),
              get_middle(get_middle(rhomb1, centre), centre), canv)

    canv.create_polygon(figure[4], width = 2, fill = "", outline = "#00FFFF")

    canv.create_polygon(figure[5], width = 2, fill = "", outline = "#00FFFF")
    canv.create_polygon(figure[6], width = 2, fill = "", outline = "#00FFFF")


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


def unit_1_task(figure):
    global canv_root

    screen_figure = []
    circle = []
    left = []
    right = []

    for i in range(4):
        screen_figure.append(change_coords(figure[i]))

    for i in range(len(figure[4])):
        circle.append(change_coords(figure[4][i]))
        left.append(change_coords(figure[5][i]))
        right.append(change_coords(figure[6][i]))

    screen_figure.append(circle)
    screen_figure.append(left)
    screen_figure.append(right)


    canv.delete("all")

    create_axis(canv, change_coords((0, 0)))
    draw_figure(screen_figure, canv)

    centre = get_middle(figure[0], figure[2])
    draw_dot(centre, "#00FF00", canv)


def copy_figure(figure, back_figure):
    back_figure[0] = figure[0]
    back_figure[1] = figure[1]
    back_figure[2] = figure[2]
    back_figure[3] = figure[3]
    back_figure[4] = figure[4][:]
    back_figure[5] = figure[5][:]
    back_figure[6] = figure[6][:]


def rotate_figure(figure, moves, entr2, entr3):
    string = entr2.get()
    string = " ".join(string.split())
    string.strip()

    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён центр вращения")
    else:
        try:
            new_dots = [float(i) for i in string.split(" ")]
                    
            if len(new_dots) != 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: -4.4  10")
        else:
            angle_string = entr3.get()
            angle_string = " ".join(angle_string.split())
            angle_string.strip()
    
            if len(angle_string) == 0:
                msg.showerror("Некорректный ввод",
                              "Не введён центр вращения")
            else:
                try:
                    angle = [float(i) for i in angle_string.split(" ")]
                            
                    if len(angle) != 1:
                        raise BaseException("Must be doubled")
                except:
                    msg.showerror("Некорректный ввод",
                                  "Введите угол в правильной форме\n\
Например: -47.4  ")
                else:
                    moves.append(("rotate", -angle[0], (new_dots[0], new_dots[1])))
                    
                    for i in range(4):
                        figure[i] = rotate_dot(figure[i], angle[0],
                                               (new_dots[0], new_dots[1]))

                    for i in range(len(figure[4])):
                        figure[4][i] = rotate_dot(figure[4][i], angle[0],
                                                  (new_dots[0], new_dots[1]))
                        figure[5][i] = rotate_dot(figure[5][i], angle[0],
                                                  (new_dots[0], new_dots[1]))
                        figure[6][i] = rotate_dot(figure[6][i], angle[0],
                                                  (new_dots[0], new_dots[1]))

                    unit_1_task(figure)


def shift_figure(figure, moves, entr):
    string = entr.get()

    string = " ".join(string.split())
    string.strip()

    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введены величины смещения")
    else:
        try:
            new_dots = [float(i) for i in string.split(" ")]
                    
            if len(new_dots) != 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите величины смещения в правильной форме\n\
Например: -44.7 100")
        else:
            moves.append(("shift", -new_dots[0], -new_dots[1]))
            
            for i in range(4):
                figure[i] = shift_dot(figure[i], new_dots[0], new_dots[1])

            for i in range(len(figure[4])):
                figure[4][i] = shift_dot(figure[4][i], new_dots[0], new_dots[1])
                figure[5][i] = shift_dot(figure[5][i], new_dots[0], new_dots[1])
                figure[6][i] = shift_dot(figure[6][i], new_dots[0], new_dots[1])

            unit_1_task(figure)


def scale_figure(figure, moves, entr2, entr4):
    string = entr2.get()
    string = " ".join(string.split())
    string.strip()

    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введён центр вращения")
    else:
        try:
            new_dots = [float(i) for i in string.split(" ")]
                    
            if len(new_dots) != 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: -4.4  10")
        else:
            ratio_string = entr4.get()
            ratio_string = " ".join(ratio_string.split())
            ratio_string.strip()
    
            if len(ratio_string) == 0:
                msg.showerror("Некорректный ввод",
                              "Не введёны кэффициенты смещения")
            else:
                try:
                    ratio = [float(i) for i in ratio_string.split(" ")]
                            
                    if len(ratio) != 2:
                        raise BaseException("Must be doubled")
                except:
                    msg.showerror("Некорректный ввод",
                                  "Введите кэффициенты смещения в правильной \
форме\nНапример: 1.5 3")
                else:
                    if np.fabs(ratio[0]) < 0.0001 or np.fabs(ratio[1]) < 0.0001:
                        previous = [0, 0, 0, 0, 0, 0, 0]
                        copy_figure(figure, previous)
                        moves.append(("go_back", previous))
                    else:
                        moves.append(("scale", 1 / ratio[0], 1 / ratio[1], (new_dots[0], new_dots[1])))
                    
                    for i in range(4):
                        figure[i] = scale_dot(figure[i], ratio[0], ratio[1],
                                              (new_dots[0], new_dots[1]))

                    for i in range(len(figure[4])):
                        figure[4][i] = scale_dot(figure[4][i], ratio[0],
                                                 ratio[1], (new_dots[0],
                                                            new_dots[1]))
                        figure[5][i] = scale_dot(figure[5][i], ratio[0],
                                                 ratio[1], (new_dots[0],
                                                            new_dots[1]))
                        figure[6][i] = scale_dot(figure[6][i], ratio[0],
                                                 ratio[1], (new_dots[0],
                                                            new_dots[1]))

                    unit_1_task(figure)


def go_back(figure, back_figure):
    copy_figure(back_figure, figure)
    unit_1_task(figure)


def go_to_default(figure, back_figure, moves):
    previous = [0, 0, 0, 0, 0, 0, 0]
    copy_figure(figure, previous)
    moves.append(("go_back", previous))
    copy_figure(back_figure, figure)
    unit_1_task(figure)


def move_back(figure, moves):
    last_move = moves[len(moves) - 1]
    if len(moves) > 1:
        moves.pop(len(moves) - 1)

    if last_move[0] == "rotate":
        for i in range(4):
            figure[i] = rotate_dot(figure[i], last_move[1],
                                   last_move[2])

        for i in range(len(figure[4])):
            figure[4][i] = rotate_dot(figure[4][i], last_move[1],
                                      last_move[2])
            figure[5][i] = rotate_dot(figure[5][i], last_move[1],
                                      last_move[2])
            figure[6][i] = rotate_dot(figure[6][i], last_move[1],
                                      last_move[2])

        unit_1_task(figure)

    if last_move[0] == "scale":
        for i in range(4):
            figure[i] = scale_dot(figure[i], last_move[1],
                                   last_move[2], last_move[3])

        for i in range(len(figure[4])):
            figure[4][i] = scale_dot(figure[4][i], last_move[1],
                                   last_move[2], last_move[3])
            figure[5][i] = scale_dot(figure[5][i], last_move[1],
                                   last_move[2], last_move[3])
            figure[6][i] = scale_dot(figure[6][i], last_move[1],
                                   last_move[2], last_move[3])

        unit_1_task(figure)

    if last_move[0] == "shift":
        for i in range(4):
            figure[i] = shift_dot(figure[i], last_move[1],
                                   last_move[2])

        for i in range(len(figure[4])):
            figure[4][i] = shift_dot(figure[4][i], last_move[1],
                                   last_move[2])
            figure[5][i] = shift_dot(figure[5][i], last_move[1],
                                   last_move[2])
            figure[6][i] = shift_dot(figure[6][i], last_move[1],
                                   last_move[2])

        unit_1_task(figure)

    if last_move[0] == "go_back":
        go_back(figure, last_move[1])


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
    circle = get_circle((0, 0), 25, "full")
    left = get_circle((-100, 0), 50, "left")
    right = get_circle((100, 0), 50, "right")
    figure = [(-100, 50), (100, 50), (100, -50),
              (-100, -50), circle, left, right]
    unit_1_task(figure)
    
    default_figure = [0, 0, 0, 0, 0, 0, 0]
    copy_figure(figure, default_figure)

    moves = []
    moves.append(("go_back", default_figure))
    
    table_app.grid()

    info_text = "Введите величины смещения по X и Y:"
    lbl1 = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl1.grid(row = 0, column = 0, columnspan = 3)

    entr1 = tk.Entry(table_app, width=15, font="Arial 14")
    entr1.grid(row = 0, column = 3)
    entr1.insert(0, "80  -40")

    info_text = "Введите координаты центра масштабирования или поворота:"
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

    btn1 = tk.Button(table_app, font="Arial 14", text="Повернуть",
                     bg="#00FFFF",
                     command=lambda : rotate_figure(figure, moves,
                                                    entr2, entr3))
    btn1.grid(row = 4, column = 0, sticky = tk.W + tk.E)
    
    btn2 = tk.Button(table_app, font="Arial 14", text="Перенести",
                     bg="#00FFFF",
                     command=lambda : shift_figure(figure, moves,
                                                   entr1))
    btn2.grid(row = 4, column = 1, sticky = tk.W + tk.E)

    btn3 = tk.Button(table_app, font="Arial 14", text="Масштабировать",
                     bg="#00FFFF",
                     command=lambda : scale_figure(figure, moves,
                                                   entr2, entr4))
    btn3.grid(row = 4, column = 2, sticky = tk.W + tk.E)

    btn7 = tk.Button(table_app, font="Arial 14", text="Информация",
                     command=lambda : info())
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
    table_root = tk.Tk()
    table_app = tk.Frame(table_root)
    table_app.pack()
    table_root.title("Основное меню")
    table_root.geometry((str(713) + 'x' + str(190)))

    canv_root = tk.Tk()
    canv_root.title("Компьютерная графика №2")
    canv_root.geometry((str(screen_width) + 'x' + str(screen_height)))
    canv_root.resizable(False, False)

    canv = tk.Canvas(canv_root, width=screen_width,
        height=screen_height, bg="#ffffff")

    canv.pack(side=tk.BOTTOM)

    main_init(table_app, canv)

    table_root.mainloop()
    canv_root.mainloop()
