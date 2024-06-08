from .Animal import Animal
from Simulator.Organisms.Organism import Type


class Wolf(Animal):
    def __init__(self, world, json=None):
        super().__init__(9, 5, world, Type.WOLF, json)

    def construct(self):
        return Wolf(self._world)
