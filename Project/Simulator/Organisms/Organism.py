import json


from abc import ABC, abstractmethod

from Simulator.Tile import Tile
from Simulator.World import World

from enum import Enum


class Type(Enum):
    ANTELOPE = "🦌"
    CYBER_SHEEP = "🤖"
    FOX = "🦊"
    HUMAN = "👨"
    SHEEP = "🐑"
    TURTLE = "🐢"
    WOLF = "🐺"
    GRASS = "🌿"
    GUARANA = "🍅"
    MILKWEED = "🌾"
    SOSNOWSKY_HOGWEED = "🍁"
    WOLF_BERRIES = "🍇"

    @property
    def symbol(self):
        return self.value

    @staticmethod
    def getTypeByInt(i):
        return list(Type)[i]


class Organism(ABC):
    def __init__(self, type, power, initiative, world: World, json=None):
        if json is None:
            self.type = type
            self.power = power
            self.initiative = initiative
            self.age = 0
            self.alive = True
            self.reproductionCooldown = 0
            self.skip = False
            self.world = world
            self.tile = None
        else:
            self.type = Type.getTypeByInt(json["type"])
            self.power = json["power"]
            self.initiative = json["initiative"]
            self.age = json["age"]
            self.alive = json["alive"]
            self.reproductionCooldown = json["reproduction_cooldown"]
            self.skip = json["skip"]
            self.world = world
            self.tile = world.getTile(json["tile_index"])

    def getType(self):
        return self.type

    def getTile(self):
        return self.tile

    def setTile(self, tile):
        self.tile = tile

    def Age(self):
        if (self.reproductionCooldown > 0):
            self.reproductionCooldown -= 1
        self.age += 1

    def setBreedCooldown(self, turns):
        self.reproductionCooldown = turns

    def die(self):
        self.alive = False

    def isDead(self):
        return not self.alive

    def isAlive(self):
        return self.alive

    def skipTurn(self):
        self.skip = True

    def unskipTurn(self):
        self.skip = False

    def isSkipped(self):
        return self.skip

    def getPower(self):
        return self.power

    def getInitiative(self):
        return self.initiative

    def getAge(self):
        return self.age

    def setPower(self, power):
        self.power = power

    def setInitiative(self, initiative):
        self.initiative = initiative

    def getSymbol(self):
        return self.type.getSymbol()

    def draw(self):
        print(self.getSymbol())

    def toJson(self):
        data = {
            "type": self.type.ordinal(),
            "power": self.power,
            "initiative": self.initiative,
            "age": self.age,
            "alive": self.alive,
            "reproduction_cooldown": self.reproductionCooldown,
            "skip": self.skip,
            "tile_index": self.tile.index if self.tile else None
        }
        return json.dumps(data)

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def collision(self, other):
        pass

    @abstractmethod
    def collisionReaction(self, other):
        pass

    @abstractmethod
    def construct(self):
        pass
