from Simulator.World import World
import os
from Utils.GUI.GUI import GUI


def main():
    os.system('cls')
    world = World(5, 5)
    world.populateWorld()
    while True:
        world.printWorld()
        # print(F"Time: {world.checkTime()}")
        # print(F"Organisms: {world.getOrganimsCount()}")
        input()
        os.system('cls')
        world.simulate()


if __name__ == "__main__":
    main()


# def buildSquareWorldPanel(self):
#         width = self.getActiveWorld().getWidth()
#         height = self.getActiveWorld().getHeight()
#         # Create a new frame for the game board
#         self.squareWorldPanelFrame = tk.Frame(self.root)

#         # Create a dictionary to store the buttons
#         self.buttons = {}

#         # Create the buttons
#         for x in range(width):
#             for y in range(height):
#                 button = tk.Button(
#                     self.squareWorldPanelFrame, height=2, width=4, text=f'({x},{y})')
#                 button.grid(row=y, column=x)

#                 # Store the button in the dictionary
#                 self.buttons[(x, y)] = button

#                 # Add a click event to the button
#                 button.bind("<Button-1>", lambda e, x=x,
#                             y=y: self.useAddOrganismPopup(x, y, button))

#     def useAddOrganismPopup(self, x, y, button):
#         # Here you can add the logic to handle the button click
#         print(f"Button at ({x}, {y}) clicked")
