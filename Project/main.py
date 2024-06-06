from Simulator.World import World
import os


def main():
    os.system('clear')
    world = World(5, 5)
    world.populateWorld()
    while True:
        world.printWorld()
        # print(F"Time: {world.checkTime()}")
        # print(F"Organisms: {world.getOrganimsCount()}")
        input()
        os.system('clear')
        world.simulate()


if __name__ == "__main__":
    main()
