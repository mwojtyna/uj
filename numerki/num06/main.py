import numpy as np
from numpy.typing import NDArray

array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]


def LU_factor_tridiagonal(diag: array, underdiag: array) -> tuple[vector, vector]:
    N = len(diag)
    l = np.zeros(N - 1)

    for i in range(1, N):
        l[i - 1] = underdiag[i - 1] / diag[i - 1]
        diag[i] -= l[i - 1] * underdiag[i - 1]

    return l, diag


def LU_solve_tridiagonal(l: vector, u: vector, b: vector, overdiag: array) -> vector:
    N = len(u)

    # backsubstitution
    x = np.zeros(N)
    x[-1] = b[-1] / u[-1]
    for i in range(N - 2, -1, -1):
        x[i] = (b[i] - overdiag[i] * x[i + 1]) / u[i]

    return x


def sherman_morrison(z: vector, v: vector, q: vector) -> vector:
    return z - ((np.dot(v, z)) / (1.0 + np.dot(v, q))) * q


def calc_eigenvector(
    diag: array,
    underdiag: array,
    overdiag: array,
    u: vector,
    v: vector,
    limit: int,
    eps: float,
):
    N = len(diag)
    y = np.ones(N, dtype=np.float64)
    y /= np.linalg.norm(y)

    L, U = LU_factor_tridiagonal(diag, underdiag)

    for i in range(limit):
        z = LU_solve_tridiagonal(L, U, y, overdiag)
        q = LU_solve_tridiagonal(L, U, u, overdiag)
        z_k = sherman_morrison(z, v, q)
        y_new = z_k / np.linalg.norm(z_k)

        if np.linalg.norm(y_new - y) <= eps:
            return (y_new, i + 1)

        y = y_new

    return (y, limit)


def main():
    np.set_printoptions(suppress=True)

    # A - tau*I - u*v^T
    tau = 0.38197
    underdiag = np.array([-1, 1, 1, -1], dtype=np.float64)
    diag = np.array([1, 2, 1, 2, 1], dtype=np.float64)
    diag -= np.ones(len(diag), dtype=np.float64) * tau
    overdiag = np.array([-1, 1, 1, -1], dtype=np.float64)
    u = np.array([1, 0, 0, 0, 1], dtype=np.float64)
    v = np.array([1, 0, 0, 0, 1], dtype=np.float64)

    eigenvector, steps = calc_eigenvector(diag, underdiag, overdiag, u, v, 1000, 1e-12)
    print("Obliczono", eigenvector, "po", steps, "krokach")


if __name__ == "__main__":
    main()
