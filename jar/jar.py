class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Who has a jar that fits a negative amount of cookies?")
        self.capacity = capacity
        self.size = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.size + n > self.capacity:
            raise ValueError("Not enough place for additional cookies :(")
        self.size += n

    def withdraw(self, n):
        if self.size - n < 0:
            raise ValueError("Not enough cookies :(")
        self.size -= n

    @property
    def capacity(self):
        return self.capacity

    @property
    def size(self):
        return self.size


def main():
    jar = Jar()
    jar.deposit(100)
    print(jar)
    jar.withdraw(50)
    #print(jar.capacity, jar.size)

main()
