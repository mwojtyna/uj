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

    for k in range(n - 2):
        x = T[k + 1 :, k]
        u = householder_vector(x)
        H = np.eye(n - k - 1) - 2.0 * (np.outer(u, u) / (np.linalg.norm(u) ** 2))

        Q = np.eye(n)
        Q[k + 1 :, k + 1 :] = H

        T = Q @ T @ Q.transpose()

    return T


# Działa in place
def givens_row(T: matrix, i: int):
    n = len(T[0])

    a = T[i, i]
    b = T[i + 1, i]
    r = np.hypot(a, b)
    c = a / r
    s = b / r

    left = max(0, i - 1)
    right = min(n - 1, i + 2)

    for col in range(left, right + 1):
        A_i_j = T[i, col]
        A_ip1_j = T[i + 1, col]

        T[i, col] = c * A_i_j + s * A_ip1_j
        T[i + 1, col] = -s * A_i_j + c * A_ip1_j


# Działa in place
def givens_col(T: matrix, i: int):
    n = len(T[0])

    a = T[i, i]
    b = T[i, i + 1]
    r = np.hypot(a, b)
    c = a / r
    s = b / r

    top = max(0, i - 1)
    bottom = min(n - 1, i + 2)

    for row in range(top, bottom + 1):
        A_i_j = T[row, i]
        A_i_jp1 = T[row, i + 1]

        T[row, i] = c * A_i_j + s * A_i_jp1
        T[row, i + 1] = -s * A_i_j + c * A_i_jp1


def qr_algorithm(T: matrix, limit: int, eps: float) -> tuple[array, int]:
    n = len(T[0])
    diag = np.diag(T)
    T = T.copy()

    for k in range(limit):
        diag_old = np.diag(T).copy()
        for i in range(n - 1):
            givens_row(T, i)
            givens_col(T, i)
        diag = np.diag(T)

        if np.linalg.norm(diag - diag_old) <= eps:
            return diag, k + 1

    return diag, limit


def main():
    np.set_printoptions(linewidth=np.inf)  # pyright: ignore[reportArgumentType]
    np.set_printoptions(suppress=True)

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
    eigenvalues, steps = qr_algorithm(T, limit=1000, eps=1e-12)

    expected = np.linalg.eig(A).eigenvalues
    print(f"Result after {steps} steps:", eigenvalues)
    print("Expected:", expected)
    print(
        "Error:",
        np.linalg.norm(np.sort(expected) - np.sort(eigenvalues)),
    )


if __name__ == "__main__":
    main()
