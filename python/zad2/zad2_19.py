# Zadanie 2.19: połączenie liczb w trzycyfrowe bloki.
L = [7, 24, 103, 5, 99, 999]

result = "".join(str(number).zfill(3) for number in L)

assert result == "007024103005099999"
print(result)
