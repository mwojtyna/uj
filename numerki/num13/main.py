import numpy as np
from numpy.typing import NDArray

num = np.float64
array = NDArray[num]


def f(x: num) -> num:
    return np.sin(np.pi * (1 + np.sqrt(x)) / (1 + x * x)) * np.exp(-x)


def trapezoidal_method(a: num, b: num, h: num) -> num:
    sum = f(a) / 2 + f(b) / 2
    while a + h < b:
        sum += f(a + h)
        a += h
    sum *= h
    return sum


def romberg(a: num, b: num, eps: num, limit: int) -> tuple[array, int]:
    # Wynik zawierający element diagonalny tabelki Romberga w każdym wierszu
    diag = []

    h = (b - a) / 2

    # indeksy odwrócone: A[k][n] = A[n][k] z wykładu
    # base case: A[0][0] = 1 podział
    prev = [h * (f(a) + f(b))]
    diag.append(prev[0])

    for k in range(1, limit + 1):
        h /= 2

        # A[k+1][0] = złożona metoda trapezów
        cur = [trapezoidal_method(a, b, h)]

        # Wypełnienie wiersza korzystając ze wzoru na A[k][n]
        factor = 1
        for n in range(1, k + 1):
            factor *= 4
            cur.append((factor * cur[n - 1] - prev[n - 1]) / (factor - 1))

        diag.append(cur[k])

        if np.abs(cur[k] - prev[k - 1]) <= eps:
            return (diag, k)

        prev = cur

    return (diag, limit)


def main():
    np.set_printoptions(suppress=True)

    # e^(-A) < 10^(-7) => A > 16.1181
    diag, steps = romberg(0, 17, 1e-7, 25)
    for i, n in enumerate(diag):
        print(i, n)


if __name__ == "__main__":
    main()
