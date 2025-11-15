import numpy as np
from numpy.typing import NDArray

# Dla przejrzystości kodu
array = NDArray[np.float64]
vector = NDArray[np.float64]
matrix = NDArray[np.float64]

N = 6


def power_method(A: matrix, eps: float, limit: int):
    # wylosuj wektor i unormuj
    e1 = np.random.rand(N)
    norm_y = np.linalg.norm(e1)
    e1 /= norm_y

    z = np.zeros(N, dtype=np.float64)
    for i in range(limit):
        z = A @ e1
        e1_new = z / np.linalg.norm(z)

        if np.linalg.norm(e1_new - e1) <= eps:
            return e1, np.linalg.norm(z), i + 1

        e1 = e1_new

    return e1, np.linalg.norm(z), limit


def power_method_second(A: matrix, e1: vector, eps: float, limit: int):
    # wylosuj wektor i unormuj
    e2 = np.random.rand(N)
    norm_y = np.linalg.norm(e2)
    e2 /= norm_y

    # ortogonalizuj względem e1 i unormuj
    e2 -= e1 * np.dot(e1, e2)
    e2 /= np.linalg.norm(e2)

    z = np.zeros(N, dtype=np.float64)
    for i in range(limit):
        z = A @ e2
        z -= e1 * np.dot(e1, z)
        e2_new = z / np.linalg.norm(z)

        if np.linalg.norm(e2_new - e2) <= eps:
            return e2, np.linalg.norm(z), i + 1

        e2 = e2_new

    return e2, np.linalg.norm(z), limit


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

    e1, lam1, steps1 = power_method(A, 1e-12, 100)
    print(f"{lam1}, {e1} after {steps1} steps")

    e2, lam2, steps2 = power_method_second(A, e1, 1e-12, 100)
    print(f"{lam2}, {e2} after {steps2} steps")

    expected = np.linalg.eig(A)
    print(f"\n|lamda1 - expected lambda1|: {abs(lam1 - expected.eigenvalues[0])}")
    print(f"||e1 - expected e1||: {np.linalg.norm(e1 - expected.eigenvectors[:,0])}")
    print(f"\n|lamda2 - expected lambda2|: {abs(lam2 - expected.eigenvalues[1])}")
    print(f"||e2 - expected e2||: {np.linalg.norm(e2 - expected.eigenvectors[:,1])}")


if __name__ == "__main__":
    main()
