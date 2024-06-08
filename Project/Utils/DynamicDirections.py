class DynamicDirections:
    __instances = {}
    __next_ordinal = 0

    def __init__(self, name):
        self.__name = name
        self.__ordinal_value = DynamicDirections.__next_ordinal
        DynamicDirections.__next_ordinal += 1

    @classmethod
    def addInstance(cls, name):
        instance = DynamicDirections(name)
        cls.__instances[name] = instance
        return instance

    @classmethod
    def get(cls, name):
        return cls.__instances.get(name)

    def ordinal(self):
        return self.__ordinal_value

    def __str__(self):
        return self.__name

    @classmethod
    def values(cls):
        return list(cls.__instances.values())

    @classmethod
    def clear(cls):
        cls.__instances.clear()
        cls.__next_ordinal = 0
