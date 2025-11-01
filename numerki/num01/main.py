import numpy as np
from numpy.typing import NDArray

# Dla przejrzystości kodu
array = NDArray[np.float64]
vector = NDArray[np.float64]


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


def sherman_morrison(z: vector, v: vector, q: vector) -> vector:
    return z - ((np.dot(v, z)) / (1.0 + np.dot(v, q))) * q


def main():
    np.set_printoptions(linewidth=np.inf)  # pyright: ignore[reportArgumentType]

    # Rozpisanie elementów diagonalnych macierzy A, oszczędzamy pamięć!
    A_diag = np.array([3, 4, 4, 4, 4, 4, 3], dtype=np.float64)
    A_subdiag = np.array([1, 1, 1, 1, 1, 1], dtype=np.float64)

    b = np.array([1, 2, 3, 4, 5, 6, 7], dtype=np.float64)
    u = v = np.array([1, 0, 0, 0, 0, 0, 1], dtype=np.float64)

    # 1. Faktoryzacja Cholesky'ego, O(n)
    C_diag, C_subdiag = cholesky_tridiagonal(A_diag, A_subdiag)

    # 2. Rozwiązanie Az=b, O(n)
    z = solve_cholesky_tridiagonal(C_diag, C_subdiag, b)

    # 3. Rozwiązanie Aq=u, O(n)
    q = solve_cholesky_tridiagonal(C_diag, C_subdiag, u)

    # 4. Rozwiąż równanie z wykorzystaniem wzoru Shermana-Morrisona, O(n)
    x = sherman_morrison(z, v, q)
    print("Wynik:", x)

    # Wypisz różnicę
    A_1 = np.array(
        [
            [4, 1, 0, 0, 0, 0, 1],
            [1, 4, 1, 0, 0, 0, 0],
            [0, 1, 4, 1, 0, 0, 0],
            [0, 0, 1, 4, 1, 0, 0],
            [0, 0, 0, 1, 4, 1, 0],
            [0, 0, 0, 0, 1, 4, 1],
            [1, 0, 0, 0, 0, 1, 4],
        ],
        dtype=np.float64,
    )
    print("Różnica:", np.matmul(A_1, x) - b)


if __name__ == "__main__":
    main()
