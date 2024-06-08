import tkinter as tk


def build_chessboard(width, height):
    root = tk.Tk()
    root.geometry("800x200")
    root.update()  # Force the window to update
    frame = tk.Frame(root)
    frame.pack(fill=tk.BOTH, expand=1)  # Make the frame fill the entire window
    root.update()  # Force the window to update
    panel_width = frame.winfo_width()
    panel_height = frame.winfo_height()
    square_size = min(panel_width // (width * 2), panel_height // (height + 1))
    for i in range(height):
        for j in range(width):
            button = tk.Button(
                frame, text=f'({j},{i})', font=("default", 20), width=3)
            x = (i - j) * square_size + panel_width // 2 - square_size
            y = (i + j) * square_size // 2
            button.place(x=x, y=y, width=square_size, height=square_size)
            button.config(command=lambda x=j, y=i: print(f'({x},{y})'))
    root.mainloop()


build_chessboard(10, 10)
