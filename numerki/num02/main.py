import numpy as np
from numpy.typing import NDArray
import matplotlib.pyplot as plt

# Dla przejrzystości kodu
array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]


class DiagMatrix:
    diag: array
    subdiag1: array
    subdiag4: array
    n: int

    def __init__(self, diag: array, subdiag: array, subdiag2: array, n: int):
        self.diag = diag
        self.subdiag1 = subdiag
        self.subdiag4 = subdiag
        self.n = n

    def mult_vector(self, x: vector) -> vector:
        N = self.n
        y = np.zeros(N, dtype=np.float64)

        for i in range(N):
            y[i] += self.diag[i] * x[i]

            if i > 0:
                y[i] += self.subdiag1[i - 1] * x[i - 1]
            if i < N - 1:
                y[i] += self.subdiag1[i] * x[i + 1]
            if i >= 4:
                y[i] += self.subdiag4[i - 4] * x[i - 4]
            if i < N - 4:
                y[i] += self.subdiag4[i] * x[i + 4]
        return y


def gauss_seidel(
    x: vector,
    A: DiagMatrix,
    b: vector,
    eps: float,
    limit: int,
) -> tuple[int, list[float]]:

    steps = 0
    x_old = x.copy()
    diffs = []

    while steps < limit:
        N = A.n
        x[0] = (b[0] - A.subdiag1[0] * x_old[1] - A.subdiag4[0] * x_old[4]) / A.diag[0]

        for i in range(1, 3 + 1):
            x[i] = (
                b[i]
                - A.subdiag1[i - 1] * x[i - 1]
                - A.subdiag1[i] * x_old[i + 1]
                - A.subdiag4[i] * x_old[i + 4]
            ) / A.diag[i]

        for i in range(4, N - 4):
            x[i] = (
                b[i]
                - A.subdiag4[i - 4] * x[i - 4]
                - A.subdiag1[i - 1] * x[i - 1]
                - A.subdiag1[i] * x_old[i + 1]
                - A.subdiag4[i] * x_old[i + 4]
            ) / A.diag[i]

        for i in range(N - 4, N - 1):
            x[i] = (
                b[i]
                - A.subdiag4[i - 4] * x[i - 4]
                - A.subdiag1[i - 1] * x[i - 1]
                - A.subdiag1[i] * x_old[i + 1]
            ) / A.diag[i]

        x[N - 1] = (
            b[0]
            - A.subdiag4[N - 1 - 4] * x[N - 1 - 4]
            - A.subdiag1[N - 1 - 1] * x[N - 1 - 1]
        ) / A.diag[N - 1]

        diff = np.linalg.norm(x - x_old)
        diffs.append(diff)

        if diff <= eps:
            break

        x_old = x.copy()
        steps += 1

    return steps, diffs


def conjugate_gradient(
    A: DiagMatrix,
    x: vector,
    b: vector,
    eps: float,
    limit: int,
) -> tuple[int, list[float]]:
    steps = 0
    diffs = []

    r = b - A.mult_vector(x)
    p = r

    while steps < limit:
        Ap = A.mult_vector(p)
        r_dot = np.dot(r, r)

        alpha = r_dot / (p.transpose() @ Ap)
        r_new = r - alpha * Ap
        beta = np.dot(r_new, r_new) / r_dot
        p_new = r_new + beta * p
        x_old = x.copy()
        x += alpha * p

        r = r_new
        p = p_new

        diffs.append(np.linalg.norm(x - x_old))
        if np.linalg.norm(r) <= eps:
            break

        steps += 1

    return steps, diffs


def check_solution(A_diag: DiagMatrix, x: vector, b: vector) -> None:
    N = A_diag.n
    A = np.zeros((N, N), dtype=np.float64)

    # główna przekątna
    np.fill_diagonal(A, A_diag.diag)

    # pod- i nadprzekątna
    for i in range(N - 1):
        A[i, i + 1] = A[i + 1, i] = A_diag.subdiag1[i]

    # przekątna odległa
    for i in range(N - 4):
        A[i, i + 4] = A[i + 4, i] = A_diag.subdiag4[i]

    # mnożenie
    Ax = A @ x
    diff = Ax - b
    norm_diff = np.linalg.norm(diff)

    print("\nSprawdzenie poprawności rozwiązania:")

    print("  i\t(Ax)[i]\t\tb[i]\t\tróżnica")
    print("-" * 50)
    for i in range(N):
        print(f"{i:3d}\t{Ax[i]:.6e}\t{b[i]:.6e}\t{diff[i]:+.2e}")

    if norm_diff < 1e-8:
        print("\nWynik poprawny - różnice są pomijalne.")
    else:
        print("\nWynik może być niepoprawny.")


def main():
    np.set_printoptions(linewidth=np.inf)  # pyright: ignore[reportArgumentType]
    N = 128

    diag = np.full(N, 4, dtype=np.float64)
    subdiag1 = np.ones(N - 1, dtype=np.float64)
    subdiag4 = np.ones(N - 4, dtype=np.float64)
    A = DiagMatrix(diag, subdiag1, subdiag4, N)
    e = np.ones(N, dtype=np.float64)

    x = np.zeros(N, dtype=np.float64)
    steps_gs, diffs_gs = gauss_seidel(x, A, e, eps=1e-12, limit=100)
    print("Wynik po", steps_gs, "iteracjach:")
    print(x)
    check_solution(A, x, e)

    x = np.zeros(N, dtype=np.float64)
    steps_cg, diffs_cg = conjugate_gradient(A, x, e, eps=1e-12, limit=100)
    print("Wynik po", steps_cg, "iteracjach:")
    print(x)
    check_solution(A, x, e)

    plt.figure(figsize=(8, 5))
    plt.semilogy(diffs_gs, label="Gauss-Seidel")
    plt.semilogy(diffs_cg, label="Conjugate Gradient")
    plt.xlabel("Iteracja k")
    plt.ylabel(r"$\|x_k - x_{k-1}\|$")
    plt.title("Tempo zbieżności metod iteracyjnych")
    plt.legend()
    plt.grid(True, which="both", ls="--")
    plt.show()


if __name__ == "__main__":
    main()
