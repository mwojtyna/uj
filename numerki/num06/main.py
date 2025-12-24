import numpy as np
from numpy.typing import NDArray

array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]


def LU_factor_tridiagonal(
    underdiag: array, diag: array, overdiag: array
) -> tuple[vector, vector]:
    n = len(diag)
    u = np.zeros(n, dtype=np.float64)
    l = np.zeros(n - 1, dtype=np.float64)

    u[0] = diag[0]

    for i in range(1, n):
        l[i - 1] = underdiag[i - 1] / u[i - 1]
        u[i] = diag[i] - l[i - 1] * overdiag[i - 1]

    return l, u


def LU_solve_tridiagonal(overdiag: array, l: vector, u: vector, b: vector) -> vector:
    n = len(b)

    # Forward substitution (Ly = b)
    y = np.zeros(n, dtype=float)
    y[0] = b[0]
    for i in range(1, n):
        y[i] = b[i] - l[i - 1] * y[i - 1]

    # Backsubstitution (Ux = y)
    x = np.zeros(n, dtype=float)
    x[-1] = y[-1] / u[-1]
    for i in range(n - 2, -1, -1):
        x[i] = (y[i] - overdiag[i] * x[i + 1]) / u[i]

    return x


def sherman_morrison(z: vector, v: vector, q: vector) -> vector:
    return z - ((np.dot(v, z)) / (1.0 + np.dot(v, q))) * q


def calc_eigenvector(
    diag: array,
    underdiag: array,
    overdiag: array,
    u_sm: vector,
    v_sm: vector,
    limit: int,
    eps: float,
):
    N = len(diag)
    y = np.ones(N, dtype=np.float64)
    y /= np.linalg.norm(y)

    l, u = LU_factor_tridiagonal(underdiag, diag, overdiag)

    for i in range(limit):
        p = LU_solve_tridiagonal(overdiag, l, u, y)
        q = LU_solve_tridiagonal(overdiag, l, u, u_sm)
        z_k = sherman_morrison(p, v_sm, q)
        y_new = z_k / np.linalg.norm(z_k)

        if np.linalg.norm(np.abs(y_new) - np.abs(y)) <= eps:
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
