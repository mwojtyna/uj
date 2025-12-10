from bisect import bisect_left
import numpy as np
from numpy.typing import NDArray
import matplotlib.pyplot as plt

array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]


def calc_ksi(values: array, h: float) -> vector:
    N = len(values)

    diag = np.full(N - 2, 4, dtype=np.float64)
    subdiag = np.full(N - 3, 1, dtype=np.float64)
    b = np.zeros(N - 2, dtype=np.float64)
    for i in range(N - 2):
        b[i] = (6 / h**2) * (values[i] - 2 * values[i + 1] + values[i + 2])

    C_diag, C_subdiag = cholesky_tridiagonal(diag, subdiag)
    ksi = np.zeros(N, dtype=np.float64)
    ksi[1 : N - 1] = solve_cholesky_tridiagonal(C_diag, C_subdiag, b)

    return ksi


def cholesky_tridiagonal(diag: array, subdiag: array) -> tuple[array, array]:
    """
    Zwraca (diagonala C, poddiagonala C)
    """

    N = len(diag)
    C_diag = np.zeros(N, dtype=np.float64)
    C_subdiag = np.zeros(N - 1, dtype=np.float64)

    C_diag[0] = np.sqrt(diag[0])
    for i in range(1, N):
        C_subdiag[i - 1] = subdiag[i - 1] / C_diag[i - 1]
        C_diag[i] = np.sqrt(diag[i] - C_subdiag[i - 1] ** 2)

    return C_diag, C_subdiag


def back_substitution_tridiagonal(diag: array, subdiag: array, b: vector) -> vector:
    N = len(diag)
    x = np.zeros(N, dtype=np.float64)

    x[-1] = b[-1] / diag[-1]
    for i in range(N - 2, -1, -1):
        x[i] = (b[i] - subdiag[i] * x[i + 1]) / diag[i]

    return x


def forward_substitution_tridiagonal(diag: array, subdiag: array, b: vector) -> vector:
    N = len(diag)
    x = np.zeros(N, dtype=np.float64)

    x[0] = b[0] / diag[0]
    for i in range(1, N):
        x[i] = (b[i] - subdiag[i - 1] * x[i - 1]) / diag[i]

    return x


def solve_cholesky_tridiagonal(C_diag: array, C_subdiag: array, b: vector) -> vector:
    # Ax=b <=> C*(C^T*x)=b, C^T*x=y, Cy=b
    y = forward_substitution_tridiagonal(C_diag, C_subdiag, b)
    x = back_substitution_tridiagonal(C_diag, C_subdiag, y)
    return x


def y_j(j: int, x: float, nodes: array, values: array, ksi: vector) -> float:
    a = (nodes[j + 1] - x) / (nodes[j + 1] - nodes[j])
    b = (x - nodes[j]) / (nodes[j + 1] - nodes[j])
    c = 1 / 6 * (a**3 - a) * (nodes[j + 1] - nodes[j]) ** 2
    d = 1 / 6 * (b**3 - b) * (nodes[j + 1] - nodes[j]) ** 2

    return a * values[j] + b * values[j + 1] + c * ksi[j] + d * ksi[j + 1]


def f(x: float):
    return 1 / (1 + 5 * (x**2))


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

    nodes = np.array([-7 / 8, -5 / 8, -3 / 8, -1 / 8, 1 / 8, 3 / 8, 5 / 8, 7 / 8])
    values = np.array([f(x) for x in nodes])
    ksi = calc_ksi(values, 2 / 8)

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
