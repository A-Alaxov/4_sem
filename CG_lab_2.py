import tkinter as tk
import tkinter.messagebox as msg
import tkinter.ttk as ttk
import numpy as np


screen_width, screen_height = 800, 800
real_width, real_height = 600, 600
min_x, max_y = -300, 300


def get_middle(dot1, dot2):
    return ((dot1[0] + dot2[0]) / 2, (dot1[1] + dot2[1]) / 2)


def rotate_dot(dot, angle, centre):
    angle = np.radians(angle)
    return (centre[0] - (centre[0] - dot[0]) * np.cos(angle) + (dot[1] - centre[1]) * np.sin(angle),
            centre[1] + (centre[0] - dot[0]) * np.sin(angle) + (dot[1] - centre[1]) * np.cos(angle))


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
    radius = np.sqrt((rhomb0[0] - centre[0]) ** 2 +
                     (rhomb0[1] - centre[1]) ** 2)

    draw_line(up_dot, down_dot, canv)
    draw_line(rotate_dot(up_dot, 90, centre),
              rotate_dot(down_dot, 90, centre), canv)

    canv.create_oval(centre[0] - radius / 2, centre[1] - radius / 2,
                     centre[0] + radius / 2, centre[1] + radius / 2,
                     width = 2, outline = "#00FFFF")

    canv.create_arc(rhomb3[0] - radius, rhomb3[1] - radius,
                    rhomb3[0] + radius, rhomb3[1] + radius,
                    start = find_angle(figure[0], rhomb3), extent = 180, width = 2, outline = "#00FFFF")
    canv.create_arc(rhomb1[0] - radius, rhomb1[1] - radius,
                    rhomb1[0] + radius, rhomb1[1] + radius,
                    start = find_angle(figure[2], rhomb1), extent = 180, width = 2, outline = "#00FFFF")


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
    global min_x
    global max_y
    global real_width
    global real_height
    global canv_root
    global text_root

    screen_figure = []

    for i in range(4):
        screen_figure.append(change_coords(figure[i]))
    
    canv.delete("all")

    create_axis(canv, change_coords((0, 0)))
    draw_figure(screen_figure, canv)

    centre = get_middle(figure[0], figure[2])
    draw_dot(centre, "#008000", canv)

def rotate_figure(figure, entr):
    string = entr.get()

    string = " ".join(string.split())
    string.strip()

    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Не введено ни одной точки")
    else:
        try:
            new_dots = [float(i) for i in string.split(" ")]
                    
            if len(new_dots) % 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: -4.4 10   6.76  -12.0")
        else:
            for i in range(4):
                figure[i] = rotate_dot(figure[i], new_dots[2], (new_dots[0], new_dots[1]))

            unit_1_task(figure)


def add_dot(event, dots, tree):
    x = (event.x - 100) * real_width / (screen_width - 200) + min_x
    y = max_y - (event.y - 100) * real_height / (screen_height - 200)
    
    dots.append(tuple([x, y, len(dots) + 1]))
    tree.insert('', tk.END, values=(len(dots), "{:.2f}".format(x),
                                    "{:.2f}".format(y)))


def table_update(dots, tree):
    tree.delete(*tree.get_children())
    
    for i in range(len(dots)):
        dots[i] = (dots[i][0], dots[i][1], i + 1)
        tree.insert('', tk.END, values=(dots[i][2], dots[i][0], dots[i][1]))


def delete_dot(dots, tree):
    elem = tree.selection()
    if not elem:
        msg.showerror("Некорректный ввод",
                      "Выберите точку в соответствующей таблице")
        return
    
    if len(elem) > 1:
        msg.showerror("Некорректный ввод", "Выберете только одну точку")
        return
    
    ind = tree.index(elem)
    dots.pop(ind)
    table_update(dots, tree)


def edit_dot(dots, tree, enter_window, entr, elem):
    string = entr.get()

    string = " ".join(string.split())
    string.strip()
    
    if len(string) == 0:
        msg.showerror("Некорректный ввод",
                      "Координаты не введены")
    else:
        try:
            new_coord = [float(i) for i in string.split(" ")]
            
            if not len(new_coord) == 2:
                raise BaseException("Must be doubled")
        except:
            msg.showerror("Некорректный ввод",
                          "Введите координаты в правильной форме\n\
Например: -4.4    10")
        else:
            ind = tree.index(elem)
            dots[ind] = (new_coord[0], new_coord[1], dots[ind][2])
            table_update(dots, tree)

    enter_window.destroy()


def dot_handle(dots, tree, table_app):
    elem = tree.selection()
    if not elem:
        msg.showerror("Некорректный ввод",
                      "Выберите точку в соответствующей таблице")
        return
    
    if len(elem) > 1:
        msg.showerror("Некорректный ввод", "Выберете только одну точку")
        return
    
    enter_window = tk.Toplevel(table_app)
    enter_window.title("Изменение точки")
    enter_window.geometry("500x170")
 
    app = tk.Frame(enter_window)
    app.pack(padx=10, pady=10, fill=tk.BOTH)
 
    info_text = "Введите новые координаты точки (разделённые пробелами):"
    lbl = tk.Label(app, text=info_text, font="Arial 14")
    lbl.pack(padx=10, pady=10, side=tk.TOP)
 
    entr = tk.Entry(app, width=30, font="Arial 14")
    entr.pack(padx=20, pady=10, side=tk.TOP)
 
    btn = tk.Button(app, text="Изменить точку", font="Arial 14",
                    command=lambda : edit_dot(dots, tree, enter_window,
                                              entr, elem))
    btn.pack(padx=20, pady=10, side=tk.TOP)
 
    enter_window.mainloop()


def info():
    msg.showinfo("Информация", "Компьютерная графика #1\n\
Разработчик: Алахов Андрей, ИУ7-42б\n\n\
Эта программа находит такие 2 треугольника, что прямая линия, \
проходящая через их тупые углы, образует наибольший угол с Ox\n\n\
Для создания точек введите их координаты в следующем формате: X Y X Y ...\n\
Также можно добавлять точки, кликая на холст: ЛКМ для добавления в 1-ое мн-во, \
ПКМ для добавления во 2-ое мн-во\n\
Для удаления или изменения точки выберите их в соответствующей таблице\n\n\
Треугольник и точки из 1-го мн-ва голубые, из 2-го мн-ва красные\n\
Результирующая линия зелёная")


def main_init(table_app):
    figure = [(-100, 50), (100, 50), (100, -50), (-100, -50)]
    unit_1_task(figure)
    
    table_app.grid()

    info_text = "Введите координаты точек (разделённые пробелами):"
    lbl = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl.grid(row = 0, column = 0, columnspan = 4)

    entr = tk.Entry(table_app, width=30, font="Arial 14")
    entr.grid(row = 1, column = 0, columnspan = 4)
    entr.insert(0, "80 40 -221 73 0 -48")

    btn1 = tk.Button(table_app, font="Arial 14", text="Повернуть",
                     bg="#00FFFF", foreground="black",
                     command=lambda : rotate_figure(figure, entr))
    btn1.grid(row = 2, column = 1, sticky = tk.E)
    
    btn2 = tk.Button(table_app, font="Arial 14", text="Добавить во 2-ое мн-во",
                     bg="#FF0000", foreground="black",
                     command=lambda : dot_handle_dialog(dots2, entr,
                                                        "#FF0000", tree2))
    btn2.grid(row = 2, column = 2, sticky = tk.W)

    btn3 = tk.Button(table_app, font="Arial 14", text="Удалить из 1-го мн-ва",
                     bg="#00FFFF", foreground="black",
                     command=lambda : delete_dot(dots1, tree1))
    btn3.grid(row = 2, column = 0, sticky = tk.E)
    
    btn4 = tk.Button(table_app, font="Arial 14", text="Удалить из 2-го мн-ва",
                     bg="#FF0000", foreground="black",
                     command=lambda : delete_dot(dots2, tree2))
    btn4.grid(row = 2, column = 3, sticky = tk.W)

    btn5 = tk.Button(table_app, font="Arial 14", text="Изменить точку из 1-го мн-ва",
                     bg="#00FFFF", foreground="black",
                     command=lambda : dot_handle(dots1, tree1, table_app))
    btn5.grid(row = 3, column = 0, columnspan = 2, sticky = tk.E)
    
    btn6 = tk.Button(table_app, font="Arial 14", text="Изменить точку из 2-го мн-ва",
                     bg="#FF0000", foreground="black",
                     command=lambda : dot_handle(dots2, tree2, table_app))
    btn6.grid(row = 3, column = 2, columnspan = 2, sticky = tk.W)

    btn7 = tk.Button(table_app, font="Arial 14", text="Информация",
                     command=lambda : info())
    btn7.grid(row = 5, column = 0, sticky = tk.E)

    btn8 = tk.Button(table_app, font="Arial 14", text="Результат",
                     bg="#008000", foreground="black",
                     command=lambda : unit_1_task(figure))
    btn8.grid(row = 5, column = 1, columnspan = 2, sticky = tk.E + tk.W)
    
    btn9 = tk.Button(table_app, font="Arial 14", text="Очистить",
                     command=lambda : delete_all(dots1, dots2, tree1, tree2))
    btn9.grid(row = 5, column = 3, sticky = tk.W)

    #Таблица
    tree1 = ttk.Treeview(table_app, show="headings")
    tree1.grid(row = 4, column = 0, columnspan = 2,
               sticky = tk.W + tk.S + tk.E + tk.N)

    #Привязка Scrollbar к таблице
    vsb = ttk.Scrollbar(table_app, orient='vertical', command=tree1.yview)
    vsb.grid(row = 4, column = 0, columnspan = 2, sticky=tk.S + tk.E + tk.N)
    tree1.configure(yscrollcommand=vsb.set)

    #Настройка колонок таблицы
    tree1["columns"]=('1','2','3')
    tree1.column('1', width=50)
    tree1.column('2', width=50)
    tree1.column('3', width=50)
    tree1.heading('1',text='#',anchor=tk.W)
    tree1.heading('2', text='X',anchor=tk.W)
    tree1.heading('3', text='Y',anchor=tk.W)

    #Таблица
    tree2 = ttk.Treeview(table_app, show="headings")
    tree2.grid(row = 4, column = 2, columnspan = 2,
               sticky = tk.W + tk.S + tk.E + tk.N)

    #Привязка Scrollbar к таблице
    vsb = ttk.Scrollbar(table_app, orient='vertical', command=tree2.yview)
    vsb.grid(row = 4, column = 2, columnspan = 2, sticky=tk.S + tk.E + tk.N)
    tree2.configure(yscrollcommand=vsb.set)

    #Настройка колонок таблицы
    tree2["columns"]=('1','2','3')
    tree2.column('1', width=50)
    tree2.column('2', width=50)
    tree2.column('3', width=50)
    tree2.heading('1',text='№',anchor=tk.W)
    tree2.heading('2', text='X',anchor=tk.W)
    tree2.heading('3', text='Y',anchor=tk.W)


if __name__ == "__main__":
    table_root = tk.Tk()
    table_app = tk.Frame(table_root)
    table_app.pack()
    table_root.title("Основное меню")
    table_root.geometry((str(855) + 'x' + str(400)))

    canv_root = tk.Tk()
    canv_root.title("Компьютерная графика №2")
    canv_root.geometry((str(screen_width) + 'x' + str(screen_height)))
    canv_root.resizable(False, False)

    canv = tk.Canvas(canv_root, width=screen_width,
        height=screen_height, bg="#ffffff")

    canv.pack(side=tk.BOTTOM)

    main_init(table_app)

    table_root.mainloop()
    canv_root.mainloop()
