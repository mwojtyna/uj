import numpy as np
from numpy.typing import NDArray
import matplotlib.pyplot as plt

num = np.float64
matrix = NDArray[num]
vector = NDArray[num]
array = NDArray[num]


def f(x: vector) -> num:
    return (1 - x[0]) ** 2 + 100 * (x[1] - x[0] ** 2) ** 2


def gradient(x: vector) -> vector:
    df_dx = -2 * (1 - x[0]) - 400 * x[0] * (x[1] - x[0] ** 2)
    df_dy = 200 * (x[1] - x[0] ** 2)
    return np.array([df_dx, df_dy], dtype=num)


def hessian(x: vector, lam: num) -> matrix:
    h_11 = 2 - 400 * x[0] * (x[1] - x[0] ** 2) + 800 * x[0] ** 2
    h_12 = -400 * x[0]
    h_22 = 200
    return np.array(
        [
            [(1 + lam) * h_11, h_12],
            [h_12, (1 + lam) * h_22],
        ],
        dtype=num,
    )


def levenberg_marquardt(
    x_0: vector, lambda_0: num, lambda_max=1e12, eps=1e-9, limit=5000
):
    x_k = x_0.copy()
    path = [x_0]

    for i in range(limit):
        lam = lambda_0
        grad = gradient(x_k)
        f_xk = f(x_k)

        if np.linalg.norm(grad) < eps:
            return x_k, path

        while True:
            hess = hessian(x_k, lam)
            z = np.linalg.solve(hess, grad)
            x_test = x_k - z
            f_xtest = f(x_test)

            if f_xtest > f_xk:
                lam *= 8
            else:
                lam /= 8
                x_k = x_test
                path.append(x_k)
                break

            if lam > lambda_max:
                raise RuntimeError("Nie znaleziono minimum")


def plot_paths(paths):
    x_min, x_max = -3, 3
    y_min, y_max = -2, 5

    x = np.linspace(x_min, x_max, 400)
    y = np.linspace(y_min, y_max, 400)
    X, Y = np.meshgrid(x, y)
    Z = (1 - X) ** 2 + 100 * (Y - X**2) ** 2

    plt.figure(figsize=(12, 8))

    levels = np.logspace(-1, 5, 20)
    # Użycie mapy kolorów 'gray' i większej przezroczystości
    plt.contour(X, Y, Z, levels=levels, cmap="gray", alpha=0.3)
    # Usunięcie paska kolorów

    for i, path in enumerate(paths):
        path_array = np.array(path)
        (line,) = plt.plot(
            path_array[:, 0],
            path_array[:, 1],
            marker=".",
            markersize=3,
            linewidth=1,
            alpha=0.8,
        )
        plt.scatter(
            path_array[0, 0],
            path_array[0, 1],
            color=line.get_color(),
            s=30,
            edgecolors="black",
            zorder=5,
        )
        plt.scatter(path_array[-1, 0], path_array[-1, 1], color="red", s=10, zorder=5)

    plt.plot(1, 1, "r*", markersize=15, label="Minimum globalne (1,1)", zorder=10)

    plt.title("Wizualizacja algorytmu Levenberga-Marquardta na funkcji Rosenbrocka")
    plt.xlabel("$x$")
    plt.ylabel("$y$")
    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)
    plt.legend(loc="upper right", fontsize="small", ncol=2)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.show()


def main():
    np.random.seed(0)
    paths = []

    for i in range(12):
        x: vector = np.random.uniform(-2, 2, size=2)

        try:
            x_min, path = levenberg_marquardt(x, 1 / 1024)
            print(f"start={x}, minimum={x_min}, kroki={len(path)}")
            paths.append(path)
        except:
            print(f"start={x}, minimum nie znalezione")

    plot_paths(paths)


if __name__ == "__main__":
    main()
