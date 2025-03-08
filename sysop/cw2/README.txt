========================================================================
Autor: Mateusz Wojtyna                                        08.03.2025
========================================================================

* Zawartość:
============
2.c - kod programu 2
potomek.c - kod programu pomocniczego do zadania 2, który wypisuje dane procesu
odpowiedzi.txt - odpowiedzi na dodatkowe pytania

* Uruchamianie:
===============
Aby uruchomić poszczególne programy:
$ make
$ ./2.x ./potomek.x      # ./potomek.x jest programem uruchamianym przez execlp() i wypisującym dane procesu

Usuwanie plików *.o, *.x:
$ make clean

Pakowanie do archiwum:
$ make tar

* Treść zadania:
================
2. Zmodyfikowac program z cwiczenia 1b tak, aby komunikaty procesow potomnych byly
wypisywane przez program uruchamiany przez funkcje execlp. Nazwe programu do uru-
chomienia przekazywac przez argumenty programu procesu macierzystego.

Ile procesow powstanie przy n-krotnym wywolaniu funkcji fork-exec jak wyzej i dlaczego?
