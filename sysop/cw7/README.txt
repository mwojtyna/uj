========================================================================
Autor: Mateusz Wojtyna                                        17.05.2025
========================================================================

* Opis
================
Program realizuje problem producenta i konsumenta przy użyciu:
 - pamięci dzielonej POSIX,
 - semaforów nazwanych POSIX,
 - bufora cyklicznego.

* Zawartość:
============
7.c - program główny
7_kons.c - program konsumujący towar
7_prod.c - program produkujący towar
buffer.h - definicje bufora
utils.h - funkcje/makra pomocnicze
lib/sem.c - biblioteka do obsługi semaforów
lib/shm.c - biblioteka do pamięci dzielonej
pseudokod.txt - pseudokod dla problemu wielu Producentów i Konsumentów z buforem cyklicznym. 
wejscie.txt - przykładowe dane wejściowe dla programu
Makefile

* Uruchamianie:
===============
Aby uruchomić program z linkowaniem statycznym:
$ make run_static

Aby uruchomić program z linkowaniem dynamicznym (ustawianie ścieżki biblioteki podczas kompilacji):
$ make run_dynamic1

Aby uruchomić program z linkowaniem dynamicznym (ustawianie ścieżki biblioteki w powłoce):
$ make run_dynamic2

Usuwanie plików zbędnych:
$ make clean

Pakowanie do archiwum:
$ make tar
