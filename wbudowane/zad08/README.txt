Program należy uruchomić z 6 argumentami oddzielonymi spacją:

- liczba zadań,
- liczba procesorów Hardware Core,
- liczba procesorów Programmable Processor,
- liczba szyn transmisyjnych,
- czy etykiety mają być zerowe (0 - nie, 1 - tak),
- nazwa pliku wyjściowego.

Po uruchomieniu program wygeneruje plik tekstowy w formacie omówionym na zajęciach.

W sekcji @tasks zależność może mieć dopisany sufiks [warunek]. Warunek jest losowany
z przygotowanej listy warunków tekstowych z prawdopodobieństwem 10%, np.:

13 1 19(10)[temperatura < 100]
