# Zadanie 4.7: spłaszczenie zagnieżdżonych sekwencji


def flatten(sequence):
    out = []
    for item in sequence:
        if isinstance(item, (list, tuple)):
            out.extend(flatten(item))
        else:
            out.append(item)

    return out


if __name__ == "__main__":
    seq = [1, 8, [5, 6], -5, [4, [5, [6, [7]]]], 9]
    flat = flatten(seq)
    assert flat == [1, 8, 5, 6, -5, 4, 5, 6, 7, 9]
    print(f"flatten({seq}) = {flat}")
