Program należy uruchomić z 6 argumentami oddzielonymi spacją:

- liczba zadań,
- liczba procesorów Hardware Core,
- liczba procesorów Programmable Processor,
- liczba szyn transmisyjnych,
- czy etykiety mają być zerowe (0 - nie, 1 - tak),
- nazwa pliku wyjściowego.

Po uruchomieniu program wygeneruje plik tekstowy w formacie omówionym na zajęciach.

Część zadań może dodatkowo zostać rozbita na niewielką liczbę podzadań. W sekcji @tasks
takie zadanie ma dopisany sufiks {n}, gdzie n to liczba podzadań, np.:

13 1 19(10){3}

Dla takich zadań sekcje @times i @cost nie zawierają wartości dla procesorów, tylko jedną
listę wartości dla podzadań, np.:

{350, 31, 300}
