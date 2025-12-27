import numpy as np
from numpy.typing import NDArray

vector = NDArray[np.complex128]
array = NDArray[np.complex128]
num = np.complex128


# Zwraca: f(z), f'(z), f''(z)
def horner(z: num, coeffs: array):
    N = len(coeffs) - 1
    p = coeffs[-1]  # f(z)
    p_prime = 0  # f'(z)
    p_prime2 = 0  # f''(z)

    for k in range(N - 1, -1, -1):
        p_prime2 = p_prime + z * p_prime2
        p_prime = p + z * p_prime
        p = p * z + coeffs[k]

    return p, p_prime, 2 * p_prime2


def laguerre(z: num, coeffs: array, eps=1e-8, limit=1000):
    n = len(coeffs) - 1

    for i in range(limit):
        P, P_prime, P_prime2 = horner(z, coeffs)

        sqrt = np.sqrt((n - 1) * ((n - 1) * P_prime**2 - n * P * P_prime2))
        denom1 = P_prime + sqrt
        denom2 = P_prime - sqrt
        denom = denom1 if abs(denom1) > abs(denom2) else denom2

        z_new = z - n * P / denom

        if np.abs(z_new - z) <= eps:
            return z_new, i + 1

        z = z_new

    return z, limit


def forward_substitution(coeffs: vector, z_0: num) -> vector:
    n = len(coeffs) - 1

    x = np.zeros(n, dtype=num)
    x[0] = coeffs[-1]
    for i in range(1, n):
        x[i] = coeffs[n - i] + z_0 * x[i - 1]

    return x


def calc_roots(coeffs: array):
    roots = []
    steps_list = []
    while len(coeffs) > 3:
        root, steps = laguerre(0, coeffs)
        roots.append(root)
        steps_list.append(steps)
        coeffs = forward_substitution(coeffs, root)

    roots.extend(np.roots(coeffs))  # Ostatnie 2 liczymy z delty
    return roots, steps_list


def main():
    coeffs = np.array([1, -1j, -1, 1j, 1], dtype=num)  # a_0, ... ,a_n
    roots, steps = calc_roots(coeffs)
    print(roots, steps)


if __name__ == "__main__":
    main()
