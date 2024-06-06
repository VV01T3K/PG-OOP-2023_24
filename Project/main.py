from Simulator.World import World
import os


def main():
    world = World(5, 5)
    world.populateWorld()
    world.printWorld()
    while True:
        world.simulate()
        world.printWorld()
        input()
        os.system('clear')


if __name__ == "__main__":
    main()
