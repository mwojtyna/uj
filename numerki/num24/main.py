import numpy as np
from numpy.typing import NDArray

num = np.float64
matrix = NDArray[num]
vector = NDArray[num]
array = NDArray[num]


def f(x: vector) -> num:
    return (
        0.25 * x[0] ** 4
        + x[1] ** 2
        - 0.5 * x[0] ** 2
        + 0.125 * x[0]
        + 0.0625 * (x[0] - x[1])
    )


def gradient(x: vector):
    return np.array([x[0] ** 3 - x[0] + 0.1875, 2 * x[1] - 0.0625])


def hessian(x: vector, lam: num) -> matrix:
    h_11 = 3 * x[0] ** 2 - 1
    h_12 = 0
    h_22 = 2
    return np.array(
        [
            [(1 + lam) * h_11, h_12],
            [h_12, (1 + lam) * h_22],
        ],
        dtype=num,
    )


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

    for _ in range(128):
        x = np.random.uniform(-3, 3, size=2)
        try:
            x_min, steps = levenberg_marquardt(x, 1 / 1024)
            print(f"start={x}, minimum={x_min}, kroki={steps}")
        except:
            print(f"start={x}, minimum nie znalezione")


if __name__ == "__main__":
    main()
