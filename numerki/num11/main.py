from bisect import bisect_left
import numpy as np
from numpy.typing import NDArray
import matplotlib.pyplot as plt

array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]


def calc_ksi(nodes: array, values: array) -> vector:
    N = len(nodes)
    underdiag = np.zeros(N - 3)
    diag = np.zeros(N - 2)
    overdiag = np.zeros(N - 3)
    b = np.zeros(N - 2)

    for i in range(N - 3):
        j = i + 1

        h_k = nodes[j] - nodes[j - 1]
        h_k1 = nodes[j + 1] - nodes[j]

        underdiag[i] = h_k / 6
        diag[i] = (h_k + h_k1) / 3
        overdiag[i] = h_k1 / 6

        b[i] = (values[j + 1] - values[j]) / h_k1 - (values[j] - values[j - 1]) / h_k

    # ostatni wiersz
    j = N - 2
    h_k = nodes[j] - nodes[j - 1]
    h_k1 = nodes[j + 1] - nodes[j]
    diag[-1] = (h_k + h_k1) / 3
    b[-1] = (values[j + 1] - values[j]) / h_k1 - (values[j] - values[j - 1]) / h_k

    ksi = np.zeros(N)
    ksi[1 : N - 1] = thomas_solve(diag, underdiag, overdiag, b)

    return ksi


def thomas_solve(diag: array, underdiag: array, overdiag: array, b: vector) -> vector:
    N = len(diag)
    x = np.zeros(N, dtype=np.float64)
    y = np.zeros(N, dtype=np.float64)
    u = np.zeros(N - 1, dtype=np.float64)

    l = diag[0]
    y[0] = b[0] / l
    for i in range(N - 1):
        u[i] = overdiag[i] / l
        l = diag[i + 1] - u[i] * underdiag[i]
        y[i + 1] = (b[i + 1] - underdiag[i] * y[i]) / l

    # backsubstitution
    x[-1] = y[-1]
    for i in range(N - 2, -1, -1):
        x[i] = y[i] - u[i] * x[i + 1]

    return x


def y_j(j: int, x: float, nodes: array, values: array, ksi: vector) -> float:
    a = (nodes[j + 1] - x) / (nodes[j + 1] - nodes[j])
    b = (x - nodes[j]) / (nodes[j + 1] - nodes[j])
    c = 1 / 6 * (a**3 - a) * (nodes[j + 1] - nodes[j]) ** 2
    d = 1 / 6 * (b**3 - b) * (nodes[j + 1] - nodes[j]) ** 2

    return a * values[j] + b * values[j + 1] + c * ksi[j] + d * ksi[j + 1]


def f(x: float):
    return 1 / (1 + 5 * x**2)


def sample(x: float, nodes: array, values: array, ksi: vector):
    N = len(nodes)
    j = bisect_left(nodes, x) - 1

    if j < 0:
        j = 0
    elif j > N - 2:
        j = N - 2

    return y_j(j, x, nodes, values, ksi)


def main():
    np.set_printoptions(suppress=True)

    nodes = np.array([np.cos(((2 * j - 1) / 16) * np.pi) for j in range(8, 0, -1)])
    values = np.array([f(x) for x in nodes])
    ksi = np.zeros(len(nodes))
    ksi = calc_ksi(nodes, values)

    x_plot = np.linspace(nodes[0], nodes[-1], 1000)
    y_plot = np.array([sample(x, nodes, values, ksi) for x in x_plot])
    plt.plot(x_plot, y_plot, label="Splajn", color="blue")
    plt.scatter(nodes, values, color="red", label="Punkty interpolacji", zorder=5)
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.title("Naturalny splajn kubiczny")
    plt.grid(True)
    plt.legend()
    plt.xlim(-1.25, 1.25)
    plt.show()


if __name__ == "__main__":
    main()
