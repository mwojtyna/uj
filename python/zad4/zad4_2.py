# Zadanie 4.2: funkcje zwracające pełne napisy z miarką i siatką.


def make_ruler(n: int) -> str:
    if n < 0:
        raise ValueError("n < 0")

    step = max(5, len(str(n)))
    ticks = ("|" + "." * (step - 1)) * n + "|"
    labels = "0" + "".join(f"{number:>{step}}" for number in range(1, n + 1))
    return ticks + "\n" + labels


def make_grid(rows: int, cols: int) -> str:
    if rows < 0:
        raise ValueError("rows < 0")
    if cols < 0:
        raise ValueError("cols < 0")

    border = "+---" * cols + "+"
    row = "|   " * cols + "|"
    return border + ("\n" + row + "\n" + border) * rows


if __name__ == "__main__":
    ruler = make_ruler(12)
    assert ruler == (
        "|....|....|....|....|....|....|....|....|....|....|....|....|\n"
        "0    1    2    3    4    5    6    7    8    9   10   11   12"
    )

    grid = make_grid(2, 4)
    assert grid == (
        "+---+---+---+---+\n"
        "|   |   |   |   |\n"
        "+---+---+---+---+\n"
        "|   |   |   |   |\n"
        "+---+---+---+---+"
    )

    assert make_ruler(0) == "|\n0"
    assert make_grid(0, 0) == "+"

    print(ruler)
    print()
    print(grid)
