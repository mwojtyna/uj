# Zadanie 2.14: najdłuższy wyraz i jego długość.
line = "Ala ma kota\nkot\tpije mleko"

longest_word = max(line.split(), key=len, default="")
longest_length = len(longest_word)

assert longest_word == "mleko"
assert longest_length == 5
print(longest_word)
print(longest_length)
