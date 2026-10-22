convert_1 = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D": 500, "M": 1000}
convert_2 = dict(
    [("I", 1), ("V", 5), ("X", 10), ("L", 50), ("C", 100), ("D", 500), ("M", 1000)]
)
convert_3 = dict(I=1, V=5, X=10, L=50, C=100, D=500, M=1000)


def roman2Int(s: str, convert: dict[str, int]) -> int:
    N = len(s)

    res = 0
    for i in range(N - 1):
        if convert[s[i]] >= convert[s[i + 1]]:
            res += convert[s[i]]
        else:
            res -= convert[s[i]]

    res += convert[s[-1]]
    return res


decimal = roman2Int("XLIX", convert_1)
assert decimal == 49
print(decimal)
