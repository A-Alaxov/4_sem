import tkinter as tk
import tkinter.messagebox as msg
import tkinter.ttk as ttk
import sympy as sy
import numpy as np
 
 
screen_width, screen_height = 600, 600
scale = 5
 
 
 
def delete_all(canv, dots1, dots2, tree1, tree2):
    canv.delete("for_delete")
    dots1.clear()
    dots2.clear()
    tree1.delete(*tree1.get_children())
    tree2.delete(*tree2.get_children())
 
 
def stupid_check(dot1, dot2, dot3):
    len1 = (dot1[0] - dot2[0]) ** 2 + (dot1[1] - dot2[1]) ** 2
    len2 = (dot3[0] - dot2[0]) ** 2 + (dot3[1] - dot2[1]) ** 2
    len3 = (dot1[0] - dot3[0]) ** 2 + (dot1[1] - dot3[1]) ** 2

    if np.sqrt(len1) + np.sqrt(len2) <= np.sqrt(len3) or np.sqrt(len3) + np.sqrt(len2) <= np.sqrt(len1) or np.sqrt(len1) + np.sqrt(len3) <= np.sqrt(len2):
        return 0
    if len1 + len2 < len3:
        return dot2, dot1, dot3
    if len1 + len3 < len2:
        return dot1, dot2, dot3
    if len3 + len2 < len1:
        return dot3, dot1, dot2
    return 0


def find_angle(triangle1, triangle2):
    x = triangle1[0][0] - triangle2[0][0]
    y = (300 - triangle1[0][1]) - (300 - triangle2[0][1])

    if x == 0:
        return np.pi / 2
        
    if np.arctan(y / x) < 0:
        return np.arctan(y / x) + np.pi
    
    return np.arctan(y / x)


def unit_1_task(dots1, dots2, canv):
    canv.delete("for_delete")
    
    if len(dots1) <= 2 or len(dots2) <= 2:
        msg.showinfo("Incorrect input",
            "This task requires\nmore points in the plane")
        return

    result_triangles = []
    max_angle = -3
    stupid_triangles = []
    result = ""

    for i in range(len(dots1)):
        for j in range(i+1, len(dots1)):
            for k in range(j+1, len(dots1)):
                dot_1, dot_2, dot_3 = dots1[i], dots1[j], dots1[k]

                cur_triangle = stupid_check(dot_1, dot_2, dot_3)
                if cur_triangle:
                    stupid_triangles.append(cur_triangle)

    if not len(stupid_triangles):
        msg.showinfo("Incorrect input",
            "There are not enough\nobtuse triangles")
        return

    flag = 0
    for i in range(len(dots2)):
        for j in range(i+1, len(dots2)):
            for k in range(j+1, len(dots2)):
                dot_1, dot_2, dot_3 = dots2[i], dots2[j], dots2[k]
                
                cur_triangle = stupid_check(dot_1, dot_2, dot_3)
                if cur_triangle:
                    for triangle in stupid_triangles:
                        if triangle[0][0] == cur_triangle[0][0] and triangle[0][1] == cur_triangle[0][1]:
                            flag = 1
                        else:
                            cur_angle = find_angle(triangle, cur_triangle)
                            if cur_angle > max_angle:
                                max_angle = cur_angle
                                result_triangles = triangle, cur_triangle

    if not (len(result_triangles) or flag):
        msg.showinfo("Incorrect input",
            "There are not enough\nobtuse triangles")
        return

    if flag:
        result_triangles = triangle, cur_triangle
        angle_info = "The only available obtuse angles match each other, so angle can't be calculated"
    else:
        angle_info = "Result angle: {:.2f} degrees".format(np.degrees(max_angle))

    color = ("#00FFFF", "#FF0000")
    for i in range(2):
        for j in range(3):
            canv.create_oval(
                result_triangles[i][j][0] - 5,
                result_triangles[i][j][1] - 5,
                result_triangles[i][j][0] + 5,
                result_triangles[i][j][1] + 5,
                fill=color[i],
                outline="#000000",
                tags=["dot", "for_delete"],
            )

            canv.create_text(
                result_triangles[i][j][0], result_triangles[i][j][1] + 15,
                text="№{:d}: {:.2f}, {:.2f}".format(result_triangles[i][j][2], result_triangles[i][j][0], result_triangles[i][j][1]),
                font="Arial 12", tags=["for_delete"]
            )
                
    canv.create_line(result_triangles[0][0][0], result_triangles[0][0][1], result_triangles[0][1][0], result_triangles[0][1][1],
                     result_triangles[0][1][0], result_triangles[0][1][1], result_triangles[0][2][0], result_triangles[0][2][1],
                     result_triangles[0][0][0], result_triangles[0][0][1], result_triangles[0][2][0], result_triangles[0][2][1],
                     fill="#00FFFF", tags=["triangle", "for_delete"], width=2)

    canv.create_line(result_triangles[1][0][0], result_triangles[1][0][1], result_triangles[1][1][0], result_triangles[1][1][1],
                     result_triangles[1][1][0], result_triangles[1][1][1], result_triangles[1][2][0], result_triangles[1][2][1],
                     result_triangles[1][0][0], result_triangles[1][0][1], result_triangles[1][2][0], result_triangles[1][2][1],
                     fill="#FF0000", tags=["triangle", "for_delete"], width=2)

    canv.create_line(result_triangles[0][0][0], result_triangles[0][0][1], result_triangles[1][0][0], result_triangles[1][0][1],
                     fill="#FFFF00", tags=["line", "for_delete"], width=2)

    msg.showinfo("Result",
        angle_info + "\n\n\
Triangle 1:\n№{:d}: {:.2f}, {:.2f}\n№{:d}: {:.2f}, {:.2f}\n№{:d}: {:.2f}, {:.2f}\n\n\
Triangle 2:\n№{:d}: {:.2f}, {:.2f}\n№{:d}: {:.2f}, {:.2f}\n№{:d}: {:.2f}, {:.2f}".format(result_triangles[0][0][2], result_triangles[0][0][0] - 300, 300 - result_triangles[0][0][1],
                                                    result_triangles[0][1][2], result_triangles[0][1][0] - 300, 300 - result_triangles[0][1][1],
                                                    result_triangles[0][2][2], result_triangles[0][2][0] - 300, 300 - result_triangles[0][2][1],
                                                    result_triangles[1][0][2], result_triangles[1][0][0] - 300, 300 - result_triangles[1][0][1],
                                                    result_triangles[1][1][2], result_triangles[1][1][0] - 300, 300 - result_triangles[1][1][1],
                                                    result_triangles[1][2][2], result_triangles[1][2][0] - 300, 300 - result_triangles[1][2][1]))


def dot_handle_dialog(canv, dots, entr, color, tree):
    string = entr.get().strip()
    if len(string) == 0:
        msg.showerror("Incorrect input",
                      "Enter the coordinates in the correct format")
    else:
        try:
            new_dots = [float(i) for i in string.split(" ")]
                    
            if len(new_dots) % 2:
                raise BaseException("Must be doubled")

            for i in range(len(new_dots)):
                if i % 2:
                    new_dots[i] = 300 - new_dots[i]
                else:
                    new_dots[i] = 300 + new_dots[i]
        except:
            msg.showerror("Incorrect input",
                          "Enter the coordinates in the correct format")
        else:
            coords = list(zip(new_dots[0::2], new_dots[1::2]))
            
            for coord in coords:
                dots.append((coord[0], coord[1], len(dots) + 1))
                tree.insert('', tk.END, values=(len(dots), coord[0], coord[1]))


def add_dot(event, canv, dots, tree, color):
    x = event.x - 300
    y = 300 - event.y
    
    dots.append(tuple([x + 300, 300 - y, len(dots) + 1]))
    tree.insert('', tk.END, values=(len(dots), x, y))


def create_axis(canv):
    canv.create_line(
        screen_width // 2, 0,
        screen_width // 2, screen_height,
        width=2
    )
    canv.create_line(
        0, screen_height // 2,
        screen_width, screen_height // 2,
        width=2
    )
    canv.create_line(
        screen_width // 2, 3,
        screen_width // 2 - 9, 12,
        width=2
    )
    canv.create_line(
        screen_width // 2, 3,
        screen_width // 2 + 9, 12,
        width=2
    )
    canv.create_text(
        screen_width // 2 - 15, 12,
        text="Y", font="Times 15"
    )
    canv.create_line(
        screen_width - 3, screen_height // 2,
        screen_width - 12, screen_height // 2 - 9,
        width=2
    )
    canv.create_line(
        screen_width - 3, screen_height // 2,
        screen_width - 12, screen_height // 2 + 9,
        width=2
    )
    canv.create_text(
        screen_width - 10, screen_height // 2 + 20,
        text="X", font="Times 15"
    )
    canv.create_text(
        screen_width // 2 - 10, screen_height // 2 - 12,
        text="0", font="Times 15"
    )
    canv.create_line(
        screen_width // 2 + 40, screen_height // 2 - 10,
        screen_width // 2 + 40, screen_height // 2 + 10,
        width=1
    )
    canv.create_text(
        screen_width // 2 + 40, screen_height // 2 - 20,
        text="40", font="Times 15"
    )
    canv.create_line(
        screen_width // 2 - 10, screen_height // 2 - 40,
        screen_width // 2 + 10, screen_height // 2 - 40,
        width=1
    )
    canv.create_text(
        screen_width // 2 - 25, screen_height // 2 - 40,
        text="40", font="Times 15"
    )


def info():
    msg.showinfo("Information", "Computer graphics #1\n"
                 "Developer: Alahov Andrey")


def main_init(root, table_app):
    table_app.grid()

    info_text = "Enter the coordinates of the points (separated by space)"
    lbl = tk.Label(table_app, text=info_text, font="Arial 14")
    lbl.grid(row = 0, column = 0, columnspan = 2)

    entr = tk.Entry(table_app, width=30, font="Arial 14")
    entr.grid(row = 1, column = 0, columnspan = 2)
    entr.insert(0, "80 40 -221 73 0 -48")

    btn1 = tk.Button(table_app, font="Arial 14", text="Add to first set", bg="#00FFFF", foreground="black",
                    command=lambda : dot_handle_dialog(canv, dots1, entr, "#00FFFF", tree1))
    btn1.grid(row = 2, column = 0, sticky = tk.E)
    
    btn2 = tk.Button(table_app, font="Arial 14", text="Add to second set", bg="#FF0000", foreground="black",
                    command=lambda : dot_handle_dialog(canv, dots2, entr, "#FF0000", tree2))
    btn2.grid(row = 2, column = 1, sticky = tk.W)

    #Таблица
    tree1 = ttk.Treeview(table_app, show="headings")
    tree1.grid(row = 3, column = 0, sticky = tk.W + tk.S + tk.E + tk.N)

    #Привязка Scrollbar к таблице
    vsb = ttk.Scrollbar(table_app, orient='vertical', command=tree1.yview)
    vsb.grid(row = 3, column = 0, sticky=tk.S + tk.E + tk.N)
    tree1.configure(yscrollcommand=vsb.set)

    #Настройка колонок таблицы
    tree1["columns"]=('1','2','3')
    tree1.column('1', width=50)
    tree1.column('2', width=50)
    tree1.column('3', width=50)
    tree1.heading('1',text='№',anchor=tk.W)
    tree1.heading('2', text='X',anchor=tk.W)
    tree1.heading('3', text='Y',anchor=tk.W)

    #Таблица
    tree2 = ttk.Treeview(table_app, show="headings")
    tree2.grid(row = 3, column = 1, sticky = tk.W + tk.S + tk.E + tk.N)

    #Привязка Scrollbar к таблице
    vsb = ttk.Scrollbar(table_app, orient='vertical', command=tree2.yview)
    vsb.grid(row = 3, column = 1, sticky=tk.S + tk.E + tk.N)
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
    canv = tk.Canvas(root, width=screen_width,
        height=screen_height, bg="#ffffff")

    main_menu = tk.Menu(root)
    root.config(menu=main_menu)
    main_menu.add_command(label="Info", command=lambda : info())
    main_menu.add_command(label="Do",
        command=lambda : unit_1_task(dots1, dots2, canv))
    main_menu.add_command(label="Clear",
        command=lambda : delete_all(canv, dots1, dots2, tree1, tree2))

    canv.bind("<Button-1>", lambda event : add_dot(event, canv, dots1, tree1, "#00FFFF"))
    canv.bind("<Button-3>", lambda event : add_dot(event, canv, dots2, tree2, "#FF0000"))

    create_axis(canv)

    canv.pack(side=tk.BOTTOM)


if __name__ == "__main__":
    root = tk.Tk()
    table_root = tk.Tk()
    app = tk.Frame(root)
    table_app = tk.Frame(table_root)
    app.pack()
    table_app.pack()
    root.title("Planimetric problems")
    root.geometry((str(screen_width) + 'x' + str(screen_height)))
    root.resizable(False, False)
    table_root.title("Table place")
    table_root.geometry((str(screen_width) + 'x' + str(screen_height)))

    main_init(root, table_app)

    root.mainloop()
    table_root.mainloop()
