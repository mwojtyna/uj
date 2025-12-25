import numpy as np


def f(x: float) -> float:
    return np.sin(np.pi * (1 + np.sqrt(x)) / (1 + x * x)) * np.exp(-x)


def trapezoidal_method(a: float, b: float, h: float) -> float:
    sum = f(a) / 2 + f(b) / 2
    while a + h < b:
        sum += f(a + h)
        a += h
    sum *= h
    return sum


def romberg(a: float, b: float, eps: float, limit: int) -> tuple[list[float], int]:
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
        for n in range(1, k + 1):
            factor = 4**n
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
    for n in diag:
        print(n)
    print(steps)


if __name__ == "__main__":
    main()
