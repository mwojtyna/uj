# Zadanie 4.3: silnia iteracyjnie


def factorial(n: int) -> int:
    if n < 0:
        raise ValueError("n < 0")

    out = 1
    for k in range(1, n + 1):
        out *= k
    print(f"{n}! = {out}")
    return out


if __name__ == "__main__":
    assert factorial(0) == 1
    assert factorial(1) == 1
    assert factorial(2) == 2
    assert factorial(8) == 40320
    assert factorial(12) == 479001600
