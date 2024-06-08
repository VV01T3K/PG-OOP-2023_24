
from Simulator.World import World
from Utils.GUI.GUI import GUI


def main():
    world = World()
    gui = GUI(world)
    gui.run()


if __name__ == "__main__":
    main()
