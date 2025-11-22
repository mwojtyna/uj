# pyright: reportConstantRedefinition=false

import numpy as np
from numpy.typing import NDArray

# Dla przejrzystości kodu
array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]


def householder_vector(x: vector) -> vector:
    u = x.copy()
    u[0] = x[0] + np.sign(x[0]) * np.linalg.norm(x)
    return u


def householder_tridiagonalize(A: matrix) -> matrix:
    n = len(A[0])
    T = A.copy()

    for k in range(0, n - 2):
        x = T[k + 1 :, k]
        u = householder_vector(x)
        H = np.eye(n - k - 1) - 2.0 * (np.outer(u, u) / (np.linalg.norm(u) ** 2))

        Q = np.eye(n)
        Q[k + 1 :, k + 1 :] = H

        T = Q @ T @ Q.transpose()

    return T


def main():
    """
    1. Householder do postaci trójdiagonalnej symetrycznej, O(n^3)
    2. Algorytm QR dla trójdiagonalnej symetrycznej, O(n)
    3. Zczytaj z diagonali wartości własne
    """

    np.set_printoptions(linewidth=np.inf)  # pyright: ignore[reportArgumentType]

    A = np.array(
        [
            [19 / 12, 13 / 12, 5 / 6, 5 / 6, 13 / 12, -17 / 12],
            [13 / 12, 13 / 12, 5 / 6, 5 / 6, -11 / 12, 13 / 12],
            [5 / 6, 5 / 6, 5 / 6, -1 / 6, 5 / 6, 5 / 6],
            [5 / 6, 5 / 6, -1 / 6, 5 / 6, 5 / 6, 5 / 6],
            [13 / 12, -11 / 12, 5 / 6, 5 / 6, 13 / 12, 13 / 12],
            [-17 / 12, 13 / 12, 5 / 6, 5 / 6, 13 / 12, 19 / 12],
        ],
        dtype=np.float64,
    )

    T = householder_tridiagonalize(A)
    print(T)


if __name__ == "__main__":
    main()
