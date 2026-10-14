# Zadanie 2.12: napisy z pierwszych i ostatnich znaków wyrazów.
line = "Ala ma kota\nkot\tpije mleko"
words = line.split()

first_letters = "".join(word[0] for word in words)
last_letters = "".join(word[-1] for word in words)

assert first_letters == "Amkkpm"
assert last_letters == "aaateo"
print(first_letters)
print(last_letters)
