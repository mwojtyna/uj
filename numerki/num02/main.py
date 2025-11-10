import numpy as np
from numpy.typing import NDArray

# Dla przejrzystości kodu
array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]

N = 128


class DiagMatrix:
    diag: array
    subdiag: array
    subdiag2: array

    def __init__(self, diag: array, subdiag: array, subdiag2: array):
        self.diag = diag
        self.subdiag = subdiag
        self.subdiag2 = subdiag

    def mult(self, X: matrix) -> matrix:
        y = self.diag * X

        for i in range(N - 1):
            y[i + 1] += self.subdiag[i] * X[i]
            y += self.subdiag2[i] * X[i + 1]

        for i in range(N - 4):
            y[i + 4] += self.subdiag2[i] * X[i]
            y[i] += self.subdiag2[i] * X[i + 4]

        return y


def gauss_seidel(
    x: vector,
    A: DiagMatrix,
    b: vector,
    eps: float,
    limit: int,
) -> int:

    iteration = 0
    x_old = x.copy()

    while iteration < limit:
        """
        Osobno dla:
        i = 0
        i = 1,2,3
        i = 4,...,123
        i = 124,125,126
        i = 127
        """

        x[0] = (b[0] - A.subdiag[0] * x_old[1] - A.subdiag2[0] * x_old[4]) / A.diag[0]

        for i in range(1, 3 + 1):
            x[i] = (
                b[i]
                - A.subdiag[i - 1] * x[i - 1]
                - A.subdiag[i] * x_old[i + 1]
                - A.subdiag2[i] * x_old[i + 4]
            ) / A.diag[i]

        for i in range(4, N - 4):
            x[i] = (
                b[i]
                - A.subdiag2[i - 4] * x[i - 4]
                - A.subdiag[i - 1] * x[i - 1]
                - A.subdiag[i] * x_old[i + 1]
                - A.subdiag2[i] * x_old[i + 4]
            ) / A.diag[i]

        for i in range(N - 4, N - 1):
            x[i] = (
                b[i]
                - A.subdiag2[i - 4] * x[i - 4]
                - A.subdiag[i - 1] * x[i - 1]
                - A.subdiag[i] * x_old[i + 1]
            ) / A.diag[i]

        x[N - 1] = (
            b[0]
            - A.subdiag2[N - 1 - 4] * x[N - 1 - 4]
            - A.subdiag[N - 1 - 1] * x[N - 1 - 1]
        ) / A.diag[N - 1]

        if np.linalg.norm(x - x_old) <= eps:
            break

        x_old = x.copy()
        iteration += 1

    return iteration


def check_solution(A_diag: DiagMatrix, x: vector, b: vector) -> None:
    A = np.zeros((N, N), dtype=np.float64)

    # główna przekątna
    np.fill_diagonal(A, A_diag.diag)

    # pod- i nadprzekątna
    for i in range(N - 1):
        A[i, i + 1] = A[i + 1, i] = A_diag.subdiag[i]

    # przekątna odległa
    for i in range(N - 4):
        A[i, i + 4] = A[i + 4, i] = A_diag.subdiag2[i]

    # mnożenie
    Ax = A @ x
    diff = Ax - b
    norm_diff = np.linalg.norm(diff)

    print("\nSprawdzenie poprawności rozwiązania:")

    print("  i\t(Ax)[i]\t\tb[i]\t\tróżnica")
    print("-" * 50)
    for i in range(N):  # wypisz np. tylko pierwsze 20, żeby nie zalać konsoli
        print(f"{i:3d}\t{Ax[i]:.6e}\t{b[i]:.6e}\t{diff[i]:+.2e}")

    if norm_diff < 1e-8:
        print("\n✅ Wynik poprawny - różnice są pomijalne.")
    else:
        print("\n⚠️ Wynik może być niepoprawny.")


def main():
    diag = np.full(N, 4, dtype=np.float64)
    subdiag = np.ones(N - 1, dtype=np.float64)
    subdiag2 = np.ones(N - 4, dtype=np.float64)
    A = DiagMatrix(diag, subdiag, subdiag2)

    x = np.zeros(N, dtype=np.float64)
    u = np.ones(N, np.float64)

    steps = gauss_seidel(x, A, u, eps=1e-12, limit=100)

    print("Wynik po", steps, "iteracjach:")
    print(x)

    check_solution(A, x, u)


if __name__ == "__main__":
    main()
