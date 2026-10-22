# Zadanie 3.4: wczytywanie liczb rzeczywistych i obliczanie ich sześcianów.
while True:
    try:
        text = input("Podaj liczbę rzeczywistą lub stop: ").strip()
    except EOFError, KeyboardInterrupt:
        break

    if text == "stop":
        break

    try:
        x = float(text)
    except ValueError:
        print("Błąd: wpisz liczbę rzeczywistą lub stop.")
        continue

    print(f"x = {x}, x^3 = {x ** 3}")
