from .Plant import Plant
from Simulator.Organisms.Organism import Type, Organism


class Milkweed(Plant):
    def __init__(self, world, json=None):
        super().__init__(0, world, Type.MILKWEED, json)

    def construct(self):
        return Milkweed(self._world)

    def action(self):
        super().action()
        super().action()
        super().action()
