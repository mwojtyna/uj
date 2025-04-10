========================================================================
Autor: Mateusz Wojtyna                                        xx.04.2025
========================================================================

* Zawartość:
============
5a.c - kod do zadania 5a
5b.c - kod do zadania 5b
Makefile
wejscie.txt - plik z danymi do przesyłania

* Uruchamianie:
===============
Aby uruchomić program:
$ make run_a
$ make run_b

Usuwanie plików *.o, *.x:
$ make clean

Pakowanie do archiwum:
$ make tar

* Treść zadania:
================
5a) Utworzyc potok FIFO z poziomu programu, a nastepnie uruchomic procesy Produ-
centa i Konsumenta w tym samym programie (w procesie macierzystym i potomnym
lub w dwoch potomnych). Potok usuwac w funkcji zarejestrowanej przez atexit

5b) Sprawdzic, ze potoki FIFO dzialaja dla niezaleznych procesow przez utworzenie
potoku FIFO z linii komend oraz uruchomienie procesow Producenta i Konsumenta
niezaleznie z poziomu powloki, np. w roznych terminalach – mozna uzyc polecenia:
`xterm -hold -title nazwa okna -e nazwa programu &`
dla kazdego z tych procesow w pliku Makefile (jak tez tworzenie/usuwanie potoku).
