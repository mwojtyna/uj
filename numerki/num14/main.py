import numpy as np
import matplotlib.pyplot as plt
from numpy.typing import NDArray


num = np.float64
array = NDArray[num]

A = -5
B = 5


def f(x: num) -> num:
    return np.cos((1 + x) / (x * x + 0.04)) * np.exp(-(x * x))


def trapezoidal_method(a: num, b: num, h: num) -> num:
    n = int((b - a) / h)
    sum = f(a) / 2 + f(b) / 2
    for _ in range(1, n):
        sum += f(a + h)
        a += h
    sum *= h
    return sum


def romberg(a: num, b: num, eps: num = 1e-8, limit: int = 25) -> num:
    h = (b - a) / 2

    # indeksy odwrócone: A[k][n] = A[n][k] z wykładu
    # base case: A[0][0] = 1 podział
    prev = [h * (f(a) + f(b))]

    for k in range(1, limit + 1):
        h /= 2

        # A[k+1][0] = złożona metoda trapezów
        cur = [trapezoidal_method(a, b, h)]

        # Wypełnienie wiersza korzystając ze wzoru na A[k][n]
        for n in range(1, k + 1):
            factor = 4**n
            cur.append((factor * cur[n - 1] - prev[n - 1]) / (factor - 1))

        if np.abs(cur[k] - prev[k - 1]) <= eps:
            return cur[-1]

        prev = cur

    return prev[-1]


def F(x: num):
    limit = romberg(A, B)

    if A < x < B:
        return romberg(A, x)
    elif x <= A:
        return 0
    else:
        return limit


def main():
    np.set_printoptions(suppress=True)

    # integral(-inf, inf) = integral(-inf, A) + integral(A, B) + integral(B, inf)
    # A < -4.03773
    # B > 4.03773

    limit = F(B)
    print("Granica w ∞:", limit)

    nodes = np.linspace(A, B, 1000)
    values = [F(x) for x in nodes]

    plt.plot(nodes, values)
    plt.xlabel("x")
    plt.ylabel("F(x)")
    plt.title("Wykres funkcji F(x)")
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    main()
