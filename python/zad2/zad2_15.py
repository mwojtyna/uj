# Zadanie 2.15: połączenie cyfr kolejnych dodatnich liczb całkowitych.
L = [7, 24, 103, 5]

result = "".join(str(number) for number in L)

assert result == "7241035"
print(result)
