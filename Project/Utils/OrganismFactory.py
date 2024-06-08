from Simulator.Organisms.Organism import Type
from Simulator.Organisms.Animals import *
from Simulator.Organisms.Plants import *


class OrganismFactory:
    def __init__(self, world):
        self.world = world

    def create(self, json):
        type = Type.getTypeByInt(json["type"])
        if type == Type.ANTELOPE:
            return Antelope(self.world, json)
        elif type == Type.CYBER_SHEEP:
            return CyberSheep(self.world, json)
        elif type == Type.FOX:
            return Fox(self.world, json)
        elif type == Type.HUMAN:
            return Human(self.world, json)
        elif type == Type.SHEEP:
            return Sheep(self.world, json)
        elif type == Type.TURTLE:
            return Turtle(self.world, json)
        elif type == Type.WOLF:
            return Wolf(self.world, json)
        elif type == Type.GRASS:
            return Grass(self.world, json)
        elif type == Type.GUARANA:
            return Guarana(self.world, json)
        elif type == Type.MILKWEED:
            return Milkweed(self.world, json)
        elif type == Type.SOSNOWSKY_HOGWEED:
            return SosnowskyHogweed(self.world, json)
        elif type == Type.WOLF_BERRIES:
            return WolfBerries(self.world, json)
        else:
            raise Exception("Invalid type")

    def createFromType(self, type):
        if type == Type.ANTELOPE:
            return Antelope(self.world)
        elif type == Type.CYBER_SHEEP:
            return CyberSheep(self.world)
        elif type == Type.FOX:
            return Fox(self.world)
        elif type == Type.HUMAN:
            return Human(self.world)
        elif type == Type.SHEEP:
            return Sheep(self.world)
        elif type == Type.TURTLE:
            return Turtle(self.world)
        elif type == Type.WOLF:
            return Wolf(self.world)
        elif type == Type.GRASS:
            return Grass(self.world)
        elif type == Type.GUARANA:
            return Guarana(self.world)
        elif type == Type.MILKWEED:
            return Milkweed(self.world)
        elif type == Type.SOSNOWSKY_HOGWEED:
            return SosnowskyHogweed(self.world)
        elif type == Type.WOLF_BERRIES:
            return WolfBerries(self.world)
        else:
            raise Exception("Invalid type")
