# Zadanie 2.18: liczba cyfr zero w dużej liczbie całkowitej.
number = 10 ** 100 + 1010

result = str(number).count("0")

assert result == 98
print(result)
