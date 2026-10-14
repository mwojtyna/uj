# Zadanie 2.17: sortowanie wyrazów alfabetycznie i według długości.
line = "Ala ma kota\nkot\tpije mleko"
words = line.split()

alphabetically = sorted(words)
# Wyrazy o tej samej długości zachowują kolejność z tekstu.
by_length = sorted(words, key=len)

assert alphabetically == ["Ala", "kot", "kota", "ma", "mleko", "pije"]
assert by_length == ["ma", "Ala", "kot", "kota", "pije", "mleko"]
print(alphabetically)
print(by_length)
