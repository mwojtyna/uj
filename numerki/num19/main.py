import numpy as np
from numpy.typing import NDArray

num = np.float64
array = NDArray[num]
vector = NDArray[num]


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
    N = len(nodes)
    a = np.zeros(N, dtype=np.float64)
    l = np.zeros(N, dtype=np.float64)
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


def derivative(x: num, coeffs: array):
    N = len(coeffs) - 1
    p = coeffs[-1]  # p(x)
    p_prime = 0  # p'(x)

    for k in range(N - 1, -1, -1):
        p_prime = p + x * p_prime
        p = p * x + coeffs[k]

    return p_prime


def p(alpha: num):
    x = np.array([1, 2, 3, 4, 5, 6, 7], dtype=num)
    y = np.array([1, 0, 1, alpha, 1, 0, 1], dtype=num)

    coeffs = lagrange_polynomial(x, y)
    return derivative(7, coeffs)


def main():
    p0 = p(0)
    p1 = p(1)
    B = p0
    A = p1 - p0
    alpha_0 = -B / A
    print(alpha_0)


if __name__ == "__main__":
    main()
