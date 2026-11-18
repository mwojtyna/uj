import unittest

from points import Point


class Rectangle:

    def __init__(self, x1, y1, x2, y2):
        # Zakładamy, że pt1 jest lewym dolnym, a pt2 prawym górnym rogiem.
        self.pt1 = Point(x1, y1)
        self.pt2 = Point(x2, y2)

    def __str__(self) -> str:
        return f"[{self.pt1}, {self.pt2}]"

    def __repr__(self) -> str:
        return f"Rectangle({self.pt1.x}, {self.pt1.y}, {self.pt2.x}, {self.pt2.y})"

    def __eq__(self, other) -> bool:
        return self.pt1 == other.pt1 and self.pt2 == other.pt2

    def __ne__(self, other) -> bool:
        return not self == other

    def center(self) -> Point:
        """Zwraca środek prostokąta jako obiekt Point."""
        x = (self.pt1.x + self.pt2.x) / 2
        y = (self.pt1.y + self.pt2.y) / 2
        return Point(x, y)

    def area(self) -> float:
        return (self.pt2.x - self.pt1.x) * (self.pt2.y - self.pt1.y)

    def move(self, x: float, y: float):
        """Przesuwa oba wierzchołki o wektor (x, y)."""
        self.pt1 = Point(self.pt1.x + x, self.pt1.y + y)
        self.pt2 = Point(self.pt2.x + x, self.pt2.y + y)


class TestRectangle(unittest.TestCase):
    def test_string_representations(self):
        rectangle = Rectangle(1, 2, 5, 8)
        self.assertEqual(str(rectangle), "[(1, 2), (5, 8)]")
        self.assertEqual(repr(rectangle), "Rectangle(1, 2, 5, 8)")

    def test_equality(self):
        self.assertEqual(Rectangle(1, 2, 5, 8), Rectangle(1, 2, 5, 8))
        self.assertNotEqual(Rectangle(1, 2, 5, 8), Rectangle(1, 2, 6, 8))

    def test_center_and_area(self):
        rectangle = Rectangle(1, 2, 5, 8)
        self.assertEqual(rectangle.center(), Point(3, 5))
        self.assertEqual(rectangle.area(), 24)

    def test_move(self):
        rectangle = Rectangle(1, 2, 5, 8)
        rectangle.move(-2, 3)
        self.assertEqual(rectangle, Rectangle(-1, 5, 3, 11))


if __name__ == "__main__":
    unittest.main()
