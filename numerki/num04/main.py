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


def qr_tridiagonal(A: matrix) -> tuple[matrix, matrix]:
    qr = np.linalg.qr(A)
    return qr.Q, qr.R


def qr_algorithm(A: matrix, limit: int, eps: float) -> tuple[array, int]:
    Q, R = qr_tridiagonal(A)
    diag = np.diag(A)
    A_k = A.copy()

    for k in range(limit):
        old_diag = np.diag(A_k)
        A_k = R @ Q
        Q, R = qr_tridiagonal(A_k)
        diag = np.diag(A_k)

        if np.linalg.norm(diag - old_diag) <= eps:
            return diag, k + 1

    return diag, limit


def main():
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
    eigenvalues, steps = qr_algorithm(T, limit=1000, eps=1e-12)

    print(f"Result after {steps} steps:", eigenvalues)
    print(
        "Error:",
        np.linalg.norm(np.sort(np.linalg.eig(A).eigenvalues) - np.sort(eigenvalues)),
    )


if __name__ == "__main__":
    main()
