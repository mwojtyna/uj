# Zadanie 3.5: miarka o długości x (nieujemna liczba całkowita).


# Odstęp między kreskami mieści również liczby wielocyfrowe.
def draw(x: int) -> str:
    step = max(5, len(str(x)))
    ticks = ("|" + "." * (step - 1)) * x + "|"
    labels = "0" + "".join(f"{number:>{step}}" for number in range(1, x + 1))
    return ticks + "\n" + labels


result = draw(12)
assert result == (
    "|....|....|....|....|....|....|....|....|....|....|....|....|\n"
    "0    1    2    3    4    5    6    7    8    9   10   11   12"
)
print(result)
