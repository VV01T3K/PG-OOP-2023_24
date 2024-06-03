from .Plant import Plant
from Simulator.Organisms.Organism import Type


class Grass(Plant):
    def __init__(self, world, json=None):
        super().__init__(0, world, Type.GRASS, json)

    def construct(self):
        return Grass(self.world)
