import numpy as np
from numpy.typing import NDArray

num = np.float64
matrix = NDArray[num]
vector = NDArray[num]
array = NDArray[num]


def f(x: vector) -> num:
    return (
        (1 - x[0]) ** 2
        + 100 * (x[1] - x[0] ** 2) ** 2
        + 100 * (x[2] - x[1] ** 2) ** 2
        + 100 * (x[3] - x[2] ** 2) ** 2
    )


def gradient(x):
    n = len(x)
    grad = np.zeros(n)

    grad[0] = -2 * (1 - x[0]) - 400 * x[0] * (x[1] - x[0] ** 2)

    for i in range(1, n - 1):
        grad[i] = 200 * (x[i] - x[i - 1] ** 2) - 400 * x[i] * (x[i + 1] - x[i] ** 2)

    grad[-1] = 200 * (x[-1] - x[-2] ** 2)

    return grad


def hessian(x, lam):
    n = len(x)
    H = np.zeros((n, n))

    for i in range(n - 1):
        H[i, i] += 800 * x[i] ** 2 - 400 * (x[i + 1] - x[i] ** 2) + lam
        H[i, i + 1] = -400 * x[i]
        H[i + 1, i] = -400 * x[i]
        H[i + 1, i + 1] += 200

    H[0, 0] += 2
    H[-1, -1] += lam

    return H


def levenberg_marquardt(
    x_0: vector, lambda_0: num, lambda_max=1e12, eps=1e-8, limit=5000
):
    x_k = x_0.copy()
    lam = lambda_0
    path = [x_0]

    for i in range(limit):
        grad = gradient(x_k)
        f_xk = f(x_k)

        if np.linalg.norm(grad) < eps:
            return x_k, i + 1

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


def main():
    np.random.seed(0)

    for i in range(5):
        x = np.random.uniform(-2, 2, size=4)
        x_min, steps = levenberg_marquardt(x, 1 / 1024)
        print(f"start={x}, minimum={x_min}, kroki={steps}")


if __name__ == "__main__":
    main()
