# Zadanie 3.3: liczby od 0 do 30 włącznie, poza podzielnymi przez 3.

# Rozwiązanie z pętlą for.
numbers_for = []
for number in range(31):
    if number % 3 != 0:
        numbers_for.append(number)

# Rozwiązanie z pętlą while.
numbers_while = []
number = 0
while number <= 30:
    if number % 3 != 0:
        numbers_while.append(number)
    number += 1

# 0 jest podzielne przez 3
expected = [1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 29]
assert numbers_for == expected
assert numbers_while == expected

result_for = " ".join(str(number) for number in numbers_for)
result_while = " ".join(str(number) for number in numbers_while)
print(f"for:\t{result_for}")
print(f"while:\t{result_while}")
