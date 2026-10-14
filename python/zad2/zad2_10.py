# Zadanie 2.10: liczba wyrazów w napisie wielowierszowym.
line = "  Ala ma kota\nkot\tpije mleko  "

# split() bez argumentu rozdziela po białych znakach i pomija puste części.
result = len(line.split())

assert result == 6
print(result)
