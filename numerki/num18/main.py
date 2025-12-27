import numpy as np
from numpy.typing import NDArray

num = np.float64
array = NDArray[num]
vector = NDArray[num]


def P(x: float, a: vector):
    N = len(a)

    y = 0
    tmp = 1
    for i in range(N):
        y += a[i] * tmp
        tmp *= x

    return y


def initial_interval(x_0: num, coeffs, delta=0.1, limit=100):
    a = x_0
    fa = P(a, coeffs)
    b = a + delta
    fb = P(b, coeffs)

    if fb > fa:
        # zmiana kierunku
        delta *= -1
        b = a + delta
        fb = P(b, coeffs)
        assert fa > fb

    for _ in range(limit):
        c = b + delta
        fc = P(c, coeffs)

        if fc > fb:
            return a, b, c

        a = b
        fa = fb
        b = c
        fb = fc
        delta *= 2

    raise RuntimeError("Nie znaleziono przedziału")


def brent(a: num, b: num, c: num, coeffs: array, limit=100, eps=1e-6):
    prev = abs(c - a)
    prev2 = prev

    for i in range(limit):
        fa = P(a, coeffs)
        fb = P(b, coeffs)
        fc = P(c, coeffs)
        old_b = b
        d = 0

        accept = False
        denominator = a * (fc - fb) + b * (fa - fc) + c * (fb - fa)
        if abs(denominator) > 1e-16:
            nominator = a * a * (fc - fb) + b * b * (fa - fc) + c * c * (fb - fa)
            d = nominator / (2 * denominator)

            if a < d < c and max(abs(d - a), (c - d)) < 0.5 * prev2:
                accept = True

        if not accept:
            d = (c + a) / 2

        if abs(c - a) < eps * (abs(old_b) + abs(d)):
            return d, i + 1

        fd = P(d, coeffs)
        if fd < fb:
            if d < b:
                c = b
                b = d
            else:
                a = b
                b = d
        else:
            if d < b:
                a = d
            else:
                c = d

        prev2 = prev
        prev = abs(c - a)

    raise RuntimeError("Nie znaleziono punktu (brent)")


def lagrange_basis(j: int, x: float, nodes: vector) -> float:
    N = len(nodes)
    nominator = 1.0
    denominator = 1.0

    for i in range(0, j):
        nominator *= x - nodes[i]
        denominator *= nodes[j] - nodes[i]
    for i in range(j + 1, N):
        nominator *= x - nodes[i]
        denominator *= nodes[j] - nodes[i]

    return nominator / denominator


def lagrange_polynomial(nodes: vector, values: vector) -> vector:
    """
    Zwraca współczynniki wielomianu interpolacyjnego Lagrange'a
    """
    N = len(nodes)
    a = np.zeros(N, dtype=num)
    l = np.zeros(N, dtype=num)
    values = values.copy()

    # k = 0
    for j in range(N):
        l[j] = lagrange_basis(j, 0, nodes)
        a[0] += l[j] * values[j]

    # k > 0
    for k in range(1, N):
        for j in range(N):
            values[j] = (values[j] - a[k - 1]) / nodes[j]
            a[k] += l[j] * values[j]

    return a


def main():
    nodes = np.array([-1, -0.75, -0.5, -0.25, 0.25, 0.5, 0.75, 1], dtype=num)
    values = np.array(
        [
            6,
            3.04034423828125,
            1.7421875,
            1.26361083984375,
            0.75982666015625,
            0.6328125,
            0.85809326171875,
            2,
        ],
        dtype=num,
    )
    coeffs: vector = lagrange_polynomial(nodes, values)

    a, b, c = initial_interval(0, coeffs)
    value, steps = brent(a, b, c, coeffs)
    print(f"{value} po {steps} krokach")


if __name__ == "__main__":
    main()
