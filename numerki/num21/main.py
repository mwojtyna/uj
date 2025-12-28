import numpy as np
from numpy.typing import NDArray

num = np.float64
array = NDArray[num]
vector = NDArray[num]


def triangular(x: num, r: num):
    return 2 * r * x if x < 0.5 else 2 * r * (1 - x)


def lapunov_analytical(r: num):
    return np.log(2 * r)


def lapunov_numerical(r: num, N=1_000_000):
    total = 0
    for _ in range(N):
        total += np.log(2 * r)
    return total / N


def main():
    r = np.array([3 / 4, 7 / 8, 15 / 16, 31 / 32], dtype=num)
    for r in r:
        print(
            f"r={r}: numerycznie={lapunov_numerical(r)}, analitycznie={lapunov_analytical(r)}"
        )


if __name__ == "__main__":
    main()
