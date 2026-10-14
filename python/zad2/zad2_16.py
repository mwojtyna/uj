# Zadanie 2.16: zastąpienie wszystkich wystąpień ciągu GvR.
line = "GvR stworzył Pythona.\nDziękujemy, GvR!"

result = line.replace("GvR", "Guido van Rossum")

assert result == "Guido van Rossum stworzył Pythona.\nDziękujemy, Guido van Rossum!"
print(result)
