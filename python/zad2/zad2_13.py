# Zadanie 2.13: łączna długość wyrazów (bez białych znaków).
line = "Ala ma kota\nkot\tpije mleko"

result = sum(len(word) for word in line.split())

assert result == 21
print(result)
