import numpy as np
import matplotlib.pyplot as plt
from numpy.typing import NDArray

# Dla przejrzystości kodu
vector = NDArray[np.float64]


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


def f(x: float):
    return 1 / (1 + 5 * (x**2))


def P(x: float, a: vector):
    N = len(a)

    y = 0
    tmp = 1
    for i in range(N):
        y += a[i] * tmp
        tmp *= x

    return y


def main():
    np.set_printoptions(suppress=True)

    nodes = np.array([np.cos(((2 * j - 1) / 16) * np.pi) for j in range(1, 8 + 1)])
    values = np.array([f(x) for x in nodes])

    a: vector = lagrange_polynomial(nodes, values)
    print(a)

    x_plot = np.linspace(-1.25, 1.25, 1000)
    y_plot = np.array([P(x, a) for x in x_plot])
    plt.plot(x_plot, y_plot, label="Wielomian interpolacyjny", color="blue")
    plt.scatter(nodes, values, color="red", label="Punkty interpolacji", zorder=5)
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.title("Interpolacja Lagrange'a")
    plt.grid(True)
    plt.legend()
    plt.xlim(-1.25, 1.25)
    plt.show()


if __name__ == "__main__":
    main()
