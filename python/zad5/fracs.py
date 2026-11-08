import math

ZERO = [0, 1]


def add_frac(frac1: list[int], frac2: list[int]) -> list[int]:
    validate_frac(frac1)
    validate_frac(frac2)

    if is_zero(frac1):
        return frac2
    if is_zero(frac2):
        return frac1

    if frac1[1] == frac2[1]:
        return [frac1[0] + frac2[0], frac1[1]]
    else:
        make_common_denominator(frac1, frac2)
        return [frac1[0] + frac2[0], frac1[1]]


def sub_frac(frac1: list[int], frac2: list[int]):
    frac2[0] *= -1
    return add_frac(frac1, frac2)


def mul_frac(frac1: list[int], frac2: list[int]):
    validate_frac(frac1)
    validate_frac(frac2)

    if is_zero(frac1) or is_zero(frac2):
        return ZERO

    return simplify_frac([frac1[0] * frac2[0], frac1[1] * frac2[1]])


def div_frac(frac1: list[int], frac2: list[int]) -> list[int]:
    validate_frac(frac1)
    # przy dzieleniu przez ułamek, jego licznik musi być niezerowy,
    # w innym przypadku wyszedłby ułamek z zerowym mianownikiem
    if is_zero(frac2):
        raise ZeroDivisionError(frac2)

    return simplify_frac([frac1[0] * frac2[1], frac1[1] * frac2[0]])


def is_positive(frac: list[int]) -> bool:
    return (frac[0] > 0 and frac[1] > 0) or (frac[0] < 0 and frac[1] < 0)


def is_zero(frac: list[int]):
    validate_frac(frac)
    return frac[0] == 0


def cmp_frac(frac1: list[int], frac2: list[int]):
    validate_frac(frac1)
    validate_frac(frac2)
    frac1 = simplify_frac(frac1)
    frac2 = simplify_frac(frac2)
    make_common_denominator(frac1, frac2)

    if frac1[0] < frac2[0]:
        return -1
    elif frac1[0] == frac2[0]:
        return 0
    else:
        return 1


def frac2int(frac: list[int]) -> float:
    # konwersja do int
    validate_frac(frac)
    return frac[0] / frac[1]


"""
---------- Metody pomocnicze ----------
"""


# Upraszcza ułamek, dodatkowo przesuwa znak do licznika.
def simplify_frac(frac: list[int]) -> list[int]:
    gcd = math.gcd(*frac)
    frac[0] //= gcd
    frac[1] //= gcd

    if is_positive(frac):
        frac[0] = abs(frac[0])
        frac[1] = abs(frac[1])
    else:
        frac[0] = -abs(frac[0])
        frac[1] = abs(frac[1])

    return frac


# Sprowadza do wspólnego mianownika. Zmienia argumenty in-place.
def make_common_denominator(frac1: list[int], frac2: list[int]) -> None:
    if frac1[1] == frac2[1]:
        return

    gcd = math.gcd(frac1[1], frac2[1])
    lcm = abs(frac1[1] * frac2[1]) / gcd
    frac1_factor = lcm / frac1[1]
    frac2_factor = lcm / frac2[1]

    frac1[0] *= int(frac1_factor)
    frac1[1] *= int(frac1_factor)
    frac2[0] *= int(frac2_factor)
    frac2[1] *= int(frac2_factor)


def validate_frac(frac: list[int]):
    if frac[1] == 0:
        raise ZeroDivisionError(frac)


# f1 = [-1, 2]      # -1/2
# f2 = [1, -2]      # -1/2 (niejednoznaczność)
# f3 = [0, 1]       # zero
# f4 = [0, 2]       # zero (niejednoznaczność)
# f5 = [3, 1]       # 3
# f6 = [6, 2]       # 3 (niejednoznaczność)

from typing import override
import unittest


class TestFractions(unittest.TestCase):
    def test_add_frac(self):
        self.assertEqual(add_frac([1, 4], [2, 4]), [3, 4])
        self.assertEqual(add_frac([1, 2], [1, 3]), [5, 6])
        self.assertEqual(add_frac([-1, 2], [1, 3]), [-1, 6])
        self.assertEqual(add_frac([1, 2], [-1, 3]), [1, 6])
        self.assertEqual(add_frac([-1, 2], [-1, 3]), [-5, 6])
        self.assertEqual(add_frac([-1, 2], [0, 3]), [-1, 2])
        self.assertRaises(ZeroDivisionError, lambda: add_frac([-1, 0], [1, 0]))

    def test_sub_frac(self):
        self.assertEqual(sub_frac([1, 4], [2, 4]), [-1, 4])
        self.assertEqual(sub_frac([1, 2], [1, 3]), [1, 6])
        self.assertEqual(sub_frac([-1, 2], [1, 3]), [-5, 6])
        self.assertEqual(sub_frac([1, 2], [-1, 3]), [5, 6])
        self.assertEqual(sub_frac([-1, 2], [-1, 3]), [-1, 6])
        self.assertEqual(sub_frac([-1, 2], [0, 3]), [-1, 2])
        self.assertRaises(ZeroDivisionError, lambda: add_frac([-1, 0], [1, 0]))

    def test_mul_frac(self):
        self.assertEqual(mul_frac([1, 4], [2, 4]), [1, 8])
        self.assertEqual(mul_frac([1, 2], [1, 3]), [1, 6])
        self.assertEqual(mul_frac([-1, 2], [1, 3]), [-1, 6])
        self.assertEqual(mul_frac([1, 2], [-1, 3]), [-1, 6])
        self.assertEqual(mul_frac([-1, 2], [-1, 3]), [1, 6])
        self.assertEqual(mul_frac([-1, 2], [0, 3]), ZERO)
        self.assertRaises(ZeroDivisionError, lambda: add_frac([-1, 0], [1, 0]))

    def test_div_frac(self):
        self.assertEqual(div_frac([1, 4], [2, 4]), [1, 2])
        self.assertEqual(div_frac([1, 2], [1, 3]), [3, 2])
        self.assertEqual(div_frac([-1, 2], [1, 3]), [-3, 2])
        self.assertEqual(div_frac([1, 2], [-1, 3]), [-3, 2])
        self.assertEqual(div_frac([-1, 2], [-1, 3]), [3, 2])
        self.assertEqual(div_frac([1, -2], [1, 3]), [-3, 2])
        self.assertEqual(div_frac([1, 2], [1, -3]), [-3, 2])
        self.assertEqual(div_frac([0, 2], [1, 3]), [0, 1])
        self.assertRaises(ZeroDivisionError, div_frac, [1, 2], [0, 3])
        self.assertRaises(ZeroDivisionError, div_frac, [0, 1], [0, 1])
        self.assertRaises(ZeroDivisionError, div_frac, [1, 0], [1, 3])
        self.assertRaises(ZeroDivisionError, div_frac, [1, 2], [1, 0])

    def test_is_positive(self):
        self.assertTrue(is_positive([1, 2]))
        self.assertTrue(is_positive([-1, -2]))
        self.assertFalse(is_positive([-1, 2]))
        self.assertFalse(is_positive([1, -2]))
        self.assertFalse(is_positive([0, 1]))
        self.assertFalse(is_positive([0, -2]))

    def test_is_zero(self):
        self.assertTrue(is_zero([0, 1]))
        self.assertTrue(is_zero([0, 2]))
        self.assertTrue(is_zero([0, -2]))
        self.assertFalse(is_zero([1, 2]))
        self.assertFalse(is_zero([-1, 2]))
        self.assertFalse(is_zero([1, -2]))
        self.assertRaises(ZeroDivisionError, is_zero, [1, 0])
        self.assertRaises(ZeroDivisionError, is_zero, [0, 0])

    def test_cmp_frac(self):
        cases = [
            ([1, 4], [2, 4], -1),
            ([2, 4], [1, 4], 1),
            ([1, 2], [1, 3], 1),
            ([1, 3], [1, 2], -1),
            ([1, 2], [1, 2], 0),
            ([1, 2], [2, 4], 0),
            ([-1, 2], [1, 2], -1),
            ([1, 2], [-1, 2], 1),
            ([-1, 2], [-1, 3], -1),
            ([-1, 3], [-1, 2], 1),
            ([1, -2], [-1, 2], 0),
            ([-1, -2], [1, 2], 0),
            ([1, -2], [2, -2], 1),
            ([2, -2], [1, -2], -1),
            ([0, 1], [0, -2], 0),
            ([0, 1], [1, 2], -1),
            ([0, 1], [-1, 2], 1),
            ([1, 2], [0, 1], 1),
            ([-1, 2], [0, 1], -1),
        ]
        for frac1, frac2, expected in cases:
            with self.subTest(frac1=frac1, frac2=frac2):
                self.assertEqual(cmp_frac(frac1, frac2), expected)

    def test_cmp_frac_invalid_denominator(self):
        self.assertRaises(ZeroDivisionError, cmp_frac, [1, 0], [1, 2])
        self.assertRaises(ZeroDivisionError, cmp_frac, [1, 2], [1, 0])
        self.assertRaises(ZeroDivisionError, cmp_frac, [0, 0], [0, 1])
        self.assertRaises(ZeroDivisionError, cmp_frac, [0, 1], [0, 0])

    def test_frac2int(self):
        self.assertEqual(frac2int([3, 1]), 3.0)
        self.assertEqual(frac2int([6, 2]), 3.0)
        self.assertEqual(frac2int([1, 2]), 0.5)
        self.assertEqual(frac2int([-1, 2]), -0.5)
        self.assertEqual(frac2int([1, -2]), -0.5)
        self.assertEqual(frac2int([-1, -2]), 0.5)
        self.assertEqual(frac2int([0, 2]), 0.0)
        self.assertEqual(frac2int([0, -2]), 0.0)
        self.assertAlmostEqual(frac2int([1, 3]), 0.3333333333333333)
        self.assertRaises(ZeroDivisionError, frac2int, [1, 0])
        self.assertRaises(ZeroDivisionError, frac2int, [0, 0])


if __name__ == "__main__":
    unittest.main()  # uruchamia wszystkie testy
