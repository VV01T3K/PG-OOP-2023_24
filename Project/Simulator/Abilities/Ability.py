from abc import ABC, abstractmethod
from Simulator.Organisms.Organism import Organism
from typing import Optional


class Ability(ABC):
    def __init__(self, cooldown, duration, default_cooldown=-1, default_duration=-1):
        if (default_cooldown == -1) or (default_duration == -1):
            self.___default_cooldown = cooldown
            self.___default_duration = duration + 1
            self.__cooldown = 0
            self.__duration = 0
        else:
            self.___default_cooldown = default_cooldown
            self.___default_duration = default_duration
            self.__cooldown = cooldown
            self.__duration = duration
        self.__toggle = False

    def isReady(self):
        return self.__cooldown == 0

    def isActive(self):
        return self.__duration > 0

    def getCooldown(self):
        return self.__cooldown

    def getDuration(self):
        return self.__duration

    def checkToggle(self):
        return self.__toggle

    def flipToggle(self):
        self.__toggle = not self.__toggle

    def use(self):
        if (self.isReady() and not self.isActive()):
            self.__cooldown = self.___default_cooldown
            self.__duration = self.___default_duration

    def update(self):
        if self.__duration > 0:
            self.__duration -= 1
        elif self.__cooldown > 0:
            self.__cooldown -= 1

    @abstractmethod
    def effect(self, user: Organism, other: Optional[Organism] = None):
        pass
