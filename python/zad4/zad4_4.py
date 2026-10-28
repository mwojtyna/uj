# Zadanie 4.4: fibonacci iteracyjnie


def fibonacci(n: int) -> int:
    if n < 0:
        raise ValueError("n < 0")

    if n == 0:
        return 0
    if n == 1:
        return 1

    prev2 = 0
    prev1 = 1
    cur = 1
    for _ in range(2, n + 1):
        cur = prev2 + prev1
        prev2 = prev1
        prev1 = cur

    print(f"fib({n}) = {cur}")
    return cur


if __name__ == "__main__":
    assert fibonacci(0) == 0
    assert fibonacci(1) == 1
    assert fibonacci(2) == 1
    assert fibonacci(10) == 55
    assert fibonacci(20) == 6765
