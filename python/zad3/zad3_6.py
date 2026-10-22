# Zadanie 3.6: prostokąt z x kolumn i y wierszy kratek.


def draw(x: int, y: int) -> str:
    border = "+---" * x + "+"
    row = "|   " * x + "|"
    out = border + ("\n" + row + "\n" + border) * y
    return out


result = draw(4, 2)
assert result == (
    "+---+---+---+---+\n"
    "|   |   |   |   |\n"
    "+---+---+---+---+\n"
    "|   |   |   |   |\n"
    "+---+---+---+---+"
)
print(result)
