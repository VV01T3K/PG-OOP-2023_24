from .Plant import Plant
from Simulator.Organisms.Organism import Type, Organism


class Belladonna(Plant):
    def __init__(self, world, json=None):
        super().__init__(99, world, Type.BELLADONNA, json)

    def construct(self):
        return Belladonna(self._world)

    def collisionReaction(self, other: Organism):
        other.die()
        self.die()
        self._world.addLog(
            f"{other.getSymbol()} ate {self.getSymbol()} and died!")
        return True
