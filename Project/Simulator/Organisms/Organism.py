from abc import ABC, abstractmethod

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
    BELLADONNA = "🍇"

    def getSymbol(self):
        return self.value

    def getName(self):
        return self.name.replace('_', ' ')

    def getTypeByInt(i):
        return list(Type)[i]


class Organism(ABC):
    def __init__(self, type: Type, power, initiative, world, json=None):
        if json is None:
            self._type = type
            self._power = power
            self._initiative = initiative
            self._age = 0
            self._alive = True
            self._reproductionCooldown = 0
            self._skip = False
            self._world = world
            self._tile = None
        else:
            self._type = Type.getTypeByInt(json["type"])
            self._power = json["power"]
            self._initiative = json["initiative"]
            self._age = json["age"]
            self._alive = json["alive"]
            self._reproductionCooldown = json["reproduction_cooldown"]
            self._skip = json["skip"]
            self._world = world
            self._tile = world.getTile(json["tile_index"])

    def getType(self):
        return self._type

    def getTile(self):
        return self._tile

    def setTile(self, tile):
        self._tile = tile

    def Age(self):
        if (self._reproductionCooldown > 0):
            self._reproductionCooldown -= 1
        self._age += 1

    def setBreedCooldown(self, turns):
        self._reproductionCooldown = turns

    def die(self):
        self._alive = False

    def isDead(self):
        return not self._alive

    def isAlive(self):
        return self._alive

    def skipTurn(self):
        self._skip = True

    def unskipTurn(self):
        self._skip = False

    def isSkipped(self):
        return self._skip

    def getPower(self):
        return self._power

    def getInitiative(self):
        return self._initiative

    def getAge(self):
        return self._age

    def setPower(self, power):
        self._power = power

    def setInitiative(self, initiative):
        self._initiative = initiative

    def getSymbol(self):
        return self._type.value

    def toJson(self):
        json = {
            "type": list(Type).index(self._type),
            "power": self._power,
            "initiative": self._initiative,
            "age": self._age,
            "alive": self._alive,
            "reproduction_cooldown": self._reproductionCooldown,
            "skip": self._skip,
            "tile_index": self._tile.INDEX if self._tile else None
        }
        return json

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
