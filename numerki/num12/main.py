import numpy as np
import matplotlib.pyplot as plt
import math
from numpy.typing import NDArray

array = NDArray[np.float64]

d = 3
eps = 1e-12


def f(x: float):
    return 1 / (1 + 5 * (x**2))


def w(k: int, n: int):
    res = 0
    for i in range(max(k - d, 0), min(k, n - d) + 1):
        res += math.comb(d, k - i)

    if (k - d) % 2 == 1:
        res *= -1

    return res


def r(x: int, n: int, nodes: array, values: array, weights):
    nominator = 0

    for k in range(0, n + 1):
        if abs(x - nodes[k]) > eps:
            nominator += (weights[k] / (x - nodes[k])) * values[k]
        else:
            return nodes[k]

    denominator = 0
    for k in range(0, n + 1):
        denominator += weights[k] / (x - nodes[k])

    return nominator / denominator


def main():
    np.set_printoptions(suppress=True)

    nodes = np.array([-7 / 8, -5 / 8, -3 / 8, -1 / 8, 1 / 8, 3 / 8, 5 / 8, 7 / 8])
    values = np.array([f(x) for x in nodes])
    n = len(nodes) - 1
    weights = [w(k, n) for k in range(0, n + 1)]

    x_plot = np.linspace(-1.25, 1.25, 1000)
    y_plot = np.array([r(x, n, nodes, values, weights) for x in x_plot])
    plt.plot(x_plot, y_plot, label="Wielomian interpolacyjny", color="blue")
    plt.scatter(nodes, values, color="red", label="Punkty interpolacji", zorder=5)
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.title("Algorytm Floatera i Hormana")
    plt.grid(True)
    plt.legend()
    plt.xlim(-1.25, 1.25)
    plt.show()


if __name__ == "__main__":
    main()
