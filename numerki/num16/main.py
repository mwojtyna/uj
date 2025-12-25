import numpy as np
from numpy.typing import NDArray

matrix = NDArray[np.float64]
vector = NDArray[np.float64]
array = NDArray[np.float64]


def g(x: vector) -> vector:
    g_1 = 2 * x[0] ** 2 + x[1] ** 2 - 2
    g_2 = (x[0] - 0.5) ** 2 + (x[1] - 1) ** 2 - 0.25
    return np.array([g_1, g_2])


def jacobian(x: vector) -> matrix:
    j_11 = 4 * x[0]
    j_12 = 2 * x[1]
    j_21 = 2 * x[0] - 1
    j_22 = 2 * x[1] - 2
    return np.array([[j_11, j_12], [j_21, j_22]])


def newton_method(x_0: vector, eps: float = 1e-8, limit: int = 1000):
    N = 2
    x = x_0.copy()

    for i in range(limit):
        z = np.linalg.solve(jacobian(x), g(x))
        x_new = x - z

        if np.linalg.norm(x_new - x) <= eps:
            return (x_new, i + 1)

        x = x_new

    return (x, limit)


def main():
    # Dobrano punkty startowe tak, aby trafić w miejsca zerowe
    guesses = np.array([[0.6, 1], [0.4, 1]])

    for x_0 in guesses:
        x, steps = newton_method(x_0)
        print(f"Znaleziono pierwiastek x = {x} w {steps} iteracjach")


if __name__ == "__main__":
    main()
