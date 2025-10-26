import numpy as np
from numpy.typing import NDArray


matrix = NDArray[np.float64]


def cholesky(A: matrix) -> matrix:
    N = len(A)
    L = A.copy()

    for i in range(N):
        l_ii = A[i][i]
        for k in range(0, i):
            l_ii -= L[i][k] ** 2
        l_ii = np.sqrt(l_ii)
        L[i][i] = l_ii

        for k in range(i + 1, N):
            L[i][k] = 0.0

        for j in range(i + 1, N):
            l_ji = A[j][i]
            for k in range(0, i):
                l_ji -= L[j][k] * L[i][k]
            l_ji /= l_ii
            L[j][i] = l_ji

    return L


def back_substitution(U: matrix, b: matrix) -> matrix:
    N = len(U)
    x = np.array([0] * N, dtype=np.float64)
    x[N - 1] = b[N - 1] / U[N - 1][N - 1]

    for i in range(N - 2, -1, -1):
        x_i = b[i]
        for k in range(N - 1, i, -1):
            x_i -= U[i][k] * x[k]
        x_i /= U[i][i]
        x[i] = x_i

    return x


def forward_substitution(L: matrix, b: matrix) -> matrix:
    N = len(L)
    x = np.array([0] * N, dtype=np.float64)
    x[0] = b[0] / L[0][0]

    for i in range(1, N):
        x_i = b[i]
        for k in range(0, i):
            x_i -= L[i][k] * x[k]
        x_i /= L[i][i]
        x[i] = x_i

    return x


def tests():
    mat = np.array([[4, 2, 2], [2, 5, 3], [2, 3, 6]])
    print("cholesky", cholesky(mat))

    U = np.array([[3, -2, 1], [0, 1, 4], [0, 0, 2]], dtype=float)
    b = np.array([1, 2, 4], dtype=float)
    print("back_substitution", back_substitution(U, b))

    L = np.array([[2, 0, 0], [3, 1, 0], [1, -2, 1]], dtype=float)
    b = np.array([2, 5, -1], dtype=float)
    print("forward_substitution", forward_substitution(L, b))


def main():
    # Dane
    A = np.array(
        [
            [3, 1, 0, 0, 0, 0, 0],
            [1, 4, 1, 0, 0, 0, 0],
            [0, 1, 4, 1, 0, 0, 0],
            [0, 0, 1, 4, 1, 0, 0],
            [0, 0, 0, 1, 4, 1, 0],
            [0, 0, 0, 0, 1, 4, 1],
            [0, 0, 0, 0, 0, 1, 3],
        ],
        dtype=np.float64,
    )
    b = np.array([1, 2, 3, 4, 5, 6, 7], dtype=np.float64)
    u = v = np.array([1, 0, 0, 0, 0, 0, 1], dtype=np.float64)

    # 1. Faktoryzacja Cholesky'ego O(n^3)
    C = cholesky(A)
    C_T = C.transpose()

    # 2. Rozwiązanie Az=b <=> C*(C^T*z)=b
    # 2.1 Rozwiązanie Cy=b metodą forward subsitution, złożoność O(n^2)
    y_1 = forward_substitution(C, b)

    # 2.2 Rozwiązanie (C^T)*z=y metodą backsubsitution, złożoność O(n^2)
    z = back_substitution(C_T, y_1)

    # 3. Rozwiązanie Aq=u <=> C*(C^T*q)=u
    # 3.1 Rozwiązanie Cy=u metodą forward substitution, złożoność O(n^2)
    y_2 = forward_substitution(C, u)

    # 3.2 Rozwiązanie (C^T)*q=y metodą backsubsitution, złożoność O(n^2)
    q = back_substitution(C_T, y_2)

    # 4. Rozwiąż równanie
    x = z - ((np.dot(v, z)) / (1.0 + np.dot(v, q))) * q
    print(x)


if __name__ == "__main__":
    main()
