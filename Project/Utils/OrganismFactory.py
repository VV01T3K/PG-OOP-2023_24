from Simulator.Organisms.Organism import Type
from Simulator.Organisms.Animals import *
from Simulator.Organisms.Plants import *


class OrganismFactory:
    def create(self, json, world):
        type = Type.getTypeByInt(json["type"])
        if type == Type.ANTELOPE:
            return Antelope(world, json)
        elif type == Type.CYBER_SHEEP:
            return CyberSheep(world, json)
        elif type == Type.FOX:
            return Fox(world, json)
        elif type == Type.HUMAN:
            return Human(world, json)
        elif type == Type.SHEEP:
            return Sheep(world, json)
        elif type == Type.TURTLE:
            return Turtle(world, json)
        elif type == Type.WOLF:
            return Wolf(world, json)
        elif type == Type.GRASS:
            return Grass(world, json)
        elif type == Type.GUARANA:
            return Guarana(world, json)
        elif type == Type.MILKWEED:
            return Milkweed(world, json)
        elif type == Type.SOSNOWSKY_HOGWEED:
            return SosnowskyHogweed(world, json)
        elif type == Type.WOLF_BERRIES:
            return WolfBerries(world, json)
        else:
            raise Exception("Invalid type")
