from math import sqrt
import unittest


class Point:
    x: float
    y: float

    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"

    def __repr__(self) -> str:
        return f"Point({self.x}, {self.y})"

    def __eq__(self, other) -> bool:
        return self.x == other.x and self.y == other.y

    def __ne__(self, other) -> bool:
        return not self == other

    def __add__(self, other) -> Point:
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other) -> Point:
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other) -> float:
        """Zwraca iloczyn skalarny wektorów."""
        return self.x * other.x + self.y * other.y

    def cross(self, other):
        """Zwraca wartość 2D iloczynu wektorowego."""
        return self.x * other.y - self.y * other.x

    def length(self):
        return sqrt(self.x * self.x + self.y * self.y)

    def __hash__(self):
        return hash((self.x, self.y))


class TestPoint(unittest.TestCase):
    def test_string_representations(self):
        point = Point(2, -3)
        self.assertEqual(str(point), "(2, -3)")
        self.assertEqual(repr(point), "Point(2, -3)")

    def test_equality_and_hash(self):
        self.assertEqual(Point(1, 2), Point(1, 2))
        self.assertNotEqual(Point(1, 2), Point(2, 1))
        self.assertEqual(hash(Point(1, 2)), hash(Point(1, 2)))
        self.assertEqual(len({Point(1, 2), Point(1, 2)}), 1)

    def test_vector_operations(self):
        first = Point(2, 3)
        second = Point(4, -1)
        self.assertEqual(first + second, Point(6, 2))
        self.assertEqual(first - second, Point(-2, 4))
        self.assertEqual(first * second, 5)
        self.assertEqual(first.cross(second), -14)

    def test_length(self):
        self.assertEqual(Point(3, 4).length(), 5.0)
        self.assertEqual(Point(0, 0).length(), 0.0)


if __name__ == "__main__":
    unittest.main()
