from .Animal import Animal
from Simulator.Organisms.Organism import Type
from GlobalSettings import GlobalSettings
from Utils.DynamicDirections import DynamicDirections


class Human(Animal):
    def __init__(self, world, json=None):
        from Simulator.Abilities.Immortality import Immortality
        super().__init__(5, 4, world, Type.HUMAN, json)
        if (json is None):
            self.__immortality = Immortality(5, 5)
        else:
            self.__immortality = Immortality(
                json["ability_cooldown"], json["immortality_left"], 5, 5)
            if (json["immortality_left"] > 0 or json["ability_cooldown"] == 0):
                self.__immortality.use()
        self.__nextMove = DynamicDirections.get("SELF")

    def construct(self):
        return Human(self._world)

    def action(self):
        if (GlobalSettings.HUMAN_AI):
            self.__immortality.use()
            self.__immortality.update()
            super().action()
            return
        if (self.__nextMove == DynamicDirections.get("SELF")):
            return
        if (self.__immortality.checkToggle()):
            self.__immortality.use()
            self.__immortality.flipToggle()
        self.__immortality.update()
        self.move(self.__nextMove)
        self.__nextMove = DynamicDirections.get("SELF")

    def collision(self, other):
        if (self.__immortality.isActive()):
            self.__immortality.effect(self, other)
            return
        else:
            super().collision(other)

    def collisionReaction(self, other):
        if (self.__immortality.isActive()):
            self.__immortality.effect(self, other)
            return True
        else:
            return False

    def setNextMove(self, direction):
        self.__nextMove = direction

    def toggleImmortality(self):
        if (self.__immortality.isReady() and not self.__immortality.isActive()):
            self.__immortality.flipToggle()

    def getNextMove(self):
        if (self.__nextMove == DynamicDirections.get("SELF")):
            return "Give direction"
        return self.__nextMove

    def getAbilityInfo(self):
        if (self.__immortality.isActive()):
            return f"{self.__immortality.getDuration()} turns left"
        if (not self.__immortality.isReady()):
            return f"{self.__immortality.getCooldown()} turns of cooldown left"
        if (self.__immortality.checkToggle()):
            return "Using next turn"
        return "Ready to use"

    def die(self):
        if (self.__immortality.isActive()):
            self.__immortality.effect(self)
        else:
            super().die()

    def toJson(self):
        json = super().toJson()
        json["ability_cooldown"] = self.__immortality.getCooldown()
        json["immortality_left"] = self.__immortality.getDuration()
        return json
