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
