import json
import os
from pathlib import Path

from Simulator.World import World, HexWorld
from Utils.OrganismFactory import OrganismFactory


class FileHandler:
    @staticmethod
    def saveWorld(world: World, name: str):
        organisms = world.getOrganisms()
        if not organisms:
            return

        json_organisms = [organism.toJson() for organism in organisms]

        json_world = {
            "width": world.getWidth(),
            "height": world.getHeight(),
            "time": world.checkTime(),
            "hexagonal": isinstance(world, HexWorld),
        }

        data = {
            "organisms": json_organisms,
            "world": json_world
        }

        with open(f"Project/Saves/{name}.json", "w") as file:
            json.dump(data, file, indent=2)
    
    @staticmethod
    def listSaves():
        return [os.path.splitext(f.name)[0] for f in sorted(list(filter(lambda f: f.is_file(), list(Path("Project/Saves/").glob("*.json")))))]

    @staticmethod
    def loadWorld(name: str) -> World:
        with open(f"Project/Saves/{name}.json", "r") as file:
            data = json.load(file)

        world = None
        if data["world"]["hexagonal"]:
            world = HexWorld(data["world"]["width"], data["world"]["height"])
        else:
            world = World(data["world"]["width"], data["world"]["height"])
        world.setTime(data["world"]["time"])
        organisms = [OrganismFactory(world).create(organism)
                     for organism in data["organisms"]]
        world.setOrganisms(organisms)
        world.setHuman(world.findHuman())
        return world
