import tkinter as tk
import tkinter.messagebox as msg
import tkinter.ttk as ttk
import numpy as np


screen_width, screen_height = 800, 800
real_width, real_height = 600, 600
min_x, max_y = -300, 300


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


def get_len(dot1, dot2):
    return np.sqrt((dot1[0] - dot2[0]) ** 2 + (dot1[1] - dot2[1]) ** 2)
 
 
def stupid_check(dot1, dot2, dot3):
    len1 = get_len(dot1, dot2) ** 2
    len2 = get_len(dot2, dot3) ** 2
    len3 = get_len(dot3, dot1) ** 2

    if not exist_check(dot1, dot2, dot3):
        return 0
    if (len1 + len2 - len3) < -0.0000001:
        return dot2, dot1, dot3
    if (len1 + len3 - len2) < -0.0000001:
        return dot1, dot2, dot3
    if (len3 + len2 - len1) < -0.0000001:
        return dot3, dot1, dot2
    return 0


def exist_check(dot1, dot2, dot3):
    len1 = get_len(dot1, dot2)
    len2 = get_len(dot2, dot3)
    len3 = get_len(dot3, dot1)
    
    if len1 + len2 <= len3 or \
       len3 + len2 <= len1 or \
       len1 + len3 <= len2:
        return 0
    return 1


def find_angle(triangle1, triangle2):
    x = triangle1[0][0] - triangle2[0][0]
    y = triangle1[0][1] - triangle2[0][1]

    if x == 0:
        return np.pi / 2
        
    if np.arctan(y / x) < 0:
        return np.arctan(y / x) + np.pi
    
    return np.arctan(y / x)


def change_coords(dot):
    return ((dot[0] - min_x) * (screen_width - 200) / real_width + 100,
            (max_y - dot[1]) * (screen_height - 200) / real_height + 100,
            dot[2])


def draw_triangule(dot1, dot2, dot3, canv, color):
    canv.create_line(dot1[0], dot1[1], dot2[0], dot2[1],
                     dot2[0], dot2[1], dot3[0], dot3[1],
                     dot1[0], dot1[1], dot3[0], dot3[1],
                     fill=color, tags=["triangle", "for_delete"], width=2)


def draw_line(dot1, dot2, canv):
    canv.create_line(dot1[0], dot1[1], dot2[0], dot2[1],
                     fill="#008000", tags=["line", "for_delete"], width=2)


def draw_dot(dot, canv, color):
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
        text="#{:d}: ({:.2f}; {:.2f})".format(dot[2], dot[0], dot[1]),
        font="Arial 12", tags=["for_delete"]
    )

def create_axis(canv, zero_dot):
    canv.create_line(zero_dot[0], 0, zero_dot[0], screen_height, width=2)
    canv.create_line(0, zero_dot[1], screen_width, zero_dot[1], width=2)
    
    canv.create_line(zero_dot[0] - 1, 3, zero_dot[0] - 10, 12, width=2)
    canv.create_line(zero_dot[0], 3, zero_dot[0] + 9, 12, width=2)
    canv.create_text(zero_dot[0] - 15, 12, text="Y", font="Arial 15")
    
    canv.create_line(screen_width - 3, zero_dot[1], screen_width - 12,
                     zero_dot[1] - 9, width=2)
    canv.create_line(screen_width - 3, zero_dot[1], screen_width - 12,
                     zero_dot[1] + 9, width=2)
    canv.create_text(screen_width - 10, zero_dot[1] + 20, text="X",
                     font="Arial 15")
    
    canv.create_text(zero_dot[0] - 10, zero_dot[1] - 12, text="0",
                     font="Arial 15")
    
    canv.create_line(zero_dot[0] + 40, zero_dot[1] - 10, zero_dot[0] + 40,
                     zero_dot[1] + 10, width=1)
    canv.create_text(
        zero_dot[0] + 40, zero_dot[1] - 20,
        text="{:.2f}".format(40 * real_width / (screen_width - 200)),
        font="Arial 15")
    
    canv.create_line(zero_dot[0] - 10, zero_dot[1] - 40, zero_dot[0] + 10,
                     zero_dot[1] - 40, width=1)
    canv.create_text(
        zero_dot[0] - 30, zero_dot[1] - 40,
        text="{:.2f}".format(40 * real_height / (screen_height - 200)),
        font="Arial 15")


def unit_1_task(dots1, dots2, tree1, tree2):
    if len(dots1) <= 2 or len(dots2) <= 2:
        msg.showerror("Некорректный ввод",
            "Недостаточно точек для\nпостроения треугольника")
        return

    result_triangles = []
    max_angle = -3
    stupid_triangles = []
    result = ""
    existance = 0

    for i in range(len(dots1) - 2):
        for j in range(i+1, len(dots1) - 1):
            for k in range(j+1, len(dots1)):
                dot_1, dot_2, dot_3 = dots1[i], dots1[j], dots1[k]

                cur_triangle = stupid_check(dot_1, dot_2, dot_3)
                if cur_triangle:
                    stupid_triangles.append(cur_triangle)
                else:
                    existance += exist_check(dot_1, dot_2, dot_3)
    
    if not len(stupid_triangles):
        if not existance:
            msg.showinfo("Некорректный ввод",
                "Все треугольники в первом мн-ве вырожденные")
            return
    
        msg.showinfo("Некорректный ввод",
            "В первом мн-ве недостаточно\nтупых треугольников")
        return

    existance = 0
    flag = 0
    for i in range(len(dots2) - 2):
        for j in range(i+1, len(dots2) - 1):
            for k in range(j+1, len(dots2)):
                dot_1, dot_2, dot_3 = dots2[i], dots2[j], dots2[k]
                
                cur_triangle = stupid_check(dot_1, dot_2, dot_3)
                if cur_triangle:
                    for triangle in stupid_triangles:
                        if triangle[0][0] == cur_triangle[0][0] and \
                           triangle[0][1] == cur_triangle[0][1]:
                            flag = 1
                        else:
                            cur_angle = find_angle(triangle, cur_triangle)
                            if cur_angle > max_angle:
                                max_angle = cur_angle
                                result_triangles = triangle, cur_triangle
                else:
                    existance += exist_check(dot_1, dot_2, dot_3)

    if not (len(result_triangles) or flag):
        if not existance:
            msg.showinfo("Некорректный ввод",
                "Все треугольники во втором мн-ве вырожденные")
            return
    
        msg.showerror("Некорректный ввод",
            "Во втором мн-ве недостаточно\nтупых треугольников")
        return

    if flag and not len(result_triangles):
        result_triangles = triangle, cur_triangle
        angle_info = "Единственные доступные вершины тупых углов совпадают, \
поэтому угол не может быть вычислен"
    else:
        angle_info = "Получившийся угол: \
{:.2f} градусов".format(np.degrees(max_angle))

    global min_x
    global max_y
    global real_width
    global real_height
    global canv_root
    global text_root
    
    try:
        canv_root.destroy()
    except:
        pass

    try:
        text_root.destroy()
    except:
        pass

    text_root = tk.Toplevel(table_app)
    text_root.title("Результат")
    text_root.geometry("870x300")
 
    app = tk.Frame(text_root)
    app.pack()
    
    canv_root = tk.Toplevel(table_app)
    canv_root.title("Компьютерная графика №1")
    canv_root.geometry((str(screen_width) + 'x' + str(screen_height)))
    canv_root.resizable(False, False)

    canv = tk.Canvas(canv_root, width=screen_width,
        height=screen_height, bg="#ffffff")

    canv.bind("<Button-1>", lambda event : add_dot(event, dots1, tree1))
    canv.bind("<Button-3>", lambda event : add_dot(event, dots2, tree2))

    canv.pack(side=tk.BOTTOM)
    
    min_x = min(result_triangles[0][0][0], result_triangles[0][1][0],
                result_triangles[0][2][0], result_triangles[1][0][0],
                result_triangles[1][1][0], result_triangles[1][2][0], 0)
    max_x = max(result_triangles[0][0][0], result_triangles[0][1][0],
                result_triangles[0][2][0], result_triangles[1][0][0],
                result_triangles[1][1][0], result_triangles[1][2][0], 0)
    real_width = max_x - min_x

    min_y = min(result_triangles[0][0][1], result_triangles[0][1][1],
                result_triangles[0][2][1], result_triangles[1][0][1],
                result_triangles[1][1][1], result_triangles[1][2][1], 0)
    max_y = max(result_triangles[0][0][1], result_triangles[0][1][1],
                result_triangles[0][2][1], result_triangles[1][0][1],
                result_triangles[1][1][1], result_triangles[1][2][1], 0)
    real_height = max_y - min_y

    real_width, real_height= max(real_width, real_height),\
                             max(real_width, real_height)

    create_axis(canv, change_coords((0, 0, 0)))

    color = ("#00FFFF", "#FF0000")
    for i in range(2):
        draw_triangule(change_coords(result_triangles[i][0]),
                       change_coords(result_triangles[i][1]),
                       change_coords(result_triangles[i][2]), canv, color[i])
        for j in range(3):
            draw_dot(result_triangles[i][j], canv, color[i])

    draw_line(change_coords(result_triangles[0][0]),
              change_coords(result_triangles[1][0]), canv)

    result_text = angle_info + "\nЛегенда: #Номер: (X; Y); Вершина, содержащая \
тупой угол, отображается первой\n\nТреугольник 1:\n#{:d}: ({:.2f}; {:.2f})\n\
#{:d}: ({:.2f}; {:.2f})\n#{:d}: ({:.2f}; {:.2f})\n\nТреугольник 2:\n\
#{:d}: ({:.2f}; {:.2f})\n#{:d}: ({:.2f}; {:.2f})\n#{:d}: ({:.2f}; {:.2f})\
".format(result_triangles[0][0][2], result_triangles[0][0][0],
         result_triangles[0][0][1], result_triangles[0][1][2],
         result_triangles[0][1][0], result_triangles[0][1][1],
         result_triangles[0][2][2], result_triangles[0][2][0],
         result_triangles[0][2][1], result_triangles[1][0][2],
         result_triangles[1][0][0], result_triangles[1][0][1],
         result_triangles[1][1][2], result_triangles[1][1][0],
         result_triangles[1][1][1], result_triangles[1][2][2],
         result_triangles[1][2][0], result_triangles[1][2][1])
    lbl = tk.Label(app, text=result_text, font="Arial 14")
    lbl.pack()

    canv_root.mainloop()
    text_root.mainloop()


def dot_handle_dialog(dots, entr, color, tree):
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
            coords = list(zip(new_dots[0::2], new_dots[1::2]))
            
            for coord in coords:
                dots.append((coord[0], coord[1], len(dots) + 1))
                tree.insert('', tk.END, values=(len(dots), coord[0], coord[1]))


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
    table_app.grid()

    info_text = "Введите координаты точек (разделённые пробелами):"
    lbl = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl.grid(row = 0, column = 0, columnspan = 4)

    entr = tk.Entry(table_app, width=30, font="Arial 14")
    entr.grid(row = 1, column = 0, columnspan = 4)
    entr.insert(0, "80 40 -221 73 0 -48")

    btn1 = tk.Button(table_app, font="Arial 14", text="Добавить в 1-ое мн-во",
                     bg="#00FFFF", foreground="black",
                     command=lambda : dot_handle_dialog(dots1, entr,
                                                        "#00FFFF", tree1))
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
                     command=lambda : unit_1_task(dots1, dots2, tree1, tree2))
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
    
    dots1 = []
    dots2 = []


if __name__ == "__main__":
    table_root = tk.Tk()
    table_app = tk.Frame(table_root)
    table_app.pack()
    table_root.title("Основное меню")
    table_root.geometry((str(855) + 'x' + str(400)))

    main_init(table_app)

    table_root.mainloop()
