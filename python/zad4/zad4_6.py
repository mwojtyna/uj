# Zadanie 4.6: suma zagnieżdżonych sekwencji


def sum_seq(sequence) -> int:
    out = 0
    for item in sequence:
        if isinstance(item, (list, tuple)):
            out += sum_seq(item)
        else:
            out += item

    return out


if __name__ == "__main__":
    seq = [1, 8, [5, 6], -5, [4, [5, [6, [7]]]], 9]
    sum = sum_seq(seq)
    assert sum == 46
    print(f"sum({seq}) = 46")
