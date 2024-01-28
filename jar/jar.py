class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Who has a jar that fits a negative amount of cookies?")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        if self._size + n > self._capacity:
            raise ValueError("Not enough place for additional cookies :(")
        self._size += n

    def withdraw(self, n):
        if self._size - n < 0:
            raise ValueError("Not enough cookies :(")
        self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():
    jar = Jar(200)
    jar.deposit(100)
    print(str(jar))
    jar.withdraw(50)
    print(str(jar))
    print(jar.capacity, jar.size)

main()
