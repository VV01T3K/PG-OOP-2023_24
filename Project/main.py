from Simulator.World import World


def main():
    world = World(5, 5)
    world.populateWorld()
    world.printWorld()
    world.simulate()
    world.printWorld()


if __name__ == "__main__":
    main()
