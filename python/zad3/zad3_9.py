# Zadanie 3.9: sumy liczb w kolejnych sekwencjach.
sequences = [[], [4], (1, 2), [3, 4], (5, 6, 7)]

result = [sum(sequence) for sequence in sequences]

assert result == [0, 4, 3, 7, 18]
print(result)
