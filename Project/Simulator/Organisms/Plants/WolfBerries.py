from .Plant import Plant
from Simulator.Organisms.Organism import Type, Organism


class WolfBerries(Plant):
    def __init__(self, world, json=None):
        super().__init__(99, world, Type.WOLF_BERRIES, json)

    def construct(self):
        return WolfBerries(self.world)

    def collisionReaction(self, other: Organism):
        other.die()
        self.die()
        self.world.addLog(
            f"{other.getSymbol()} ate {self.getSymbol()} and died!")
        return True
