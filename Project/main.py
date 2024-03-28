import queue
import random
import statistics


class Customer:
    def __init__(self, arrival_time):
        self.arrival_time = arrival_time
        self.spent_time = 0


class Generator:
    def __init__(self):
        self.time = 0

    def generate_customer(self):
        self.time = self.time + random.expovariate(1 / 10)
        arrival_time = self.time
        return Customer(arrival_time)


class Process:
    def __init__(self, a, b):
        self.queue = queue.Queue()
        self.a, self.b = a, b

    def process(self, simulation):
        while not simulation.queue.empty():
            customer = simulation.queue.get()
            customer_arrival_time = customer.arrival_time + customer.spent_time
            if customer_arrival_time > simulation.time:
                simulation.time = customer_arrival_time
            else:
                customer.spent_time += simulation.time - customer_arrival_time
            time = random.uniform(self.a, self.b)
            customer.spent_time += time
            simulation.time += time
            self.queue.put(customer)


class Simulation:
    def __init__(self):
        self.time = 0
        self.queue = queue.Queue()
        self.generator = Generator()
        self.processes = []
        self.results = []

    def add_process(self, process):
        self.processes.append(process)

    def run(self, n):
        for i in range(n):
            customer = self.generator.generate_customer()
            self.queue.put(customer)
        for process in self.processes:
            process.process(self)
            self.time = 0
            self.queue = process.queue

    def statistics(self):
        while not self.queue.empty():
            customer = self.queue.get()
            self.results.append(customer.spent_time)
        average = statistics.mean(self.results)
        std_dev = statistics.stdev(self.results)
        return average, std_dev


simulation = Simulation()
simulation.add_process(Process(2, 3))
simulation.add_process(Process(3, 4))
simulation.run(2000)

average, std_dev = simulation.statistics()
print(f"Average: {average}")
print(f"Standard deviation: {std_dev}")
