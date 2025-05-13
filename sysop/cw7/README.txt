========================================================================
Autor: Mateusz Wojtyna                                        11.04.2025
========================================================================

* Zawartość:
============
dup.c - program do powielania procesów
worker.c - program realizujący wzajemne wykluczanie
libsem.c - biblioteka 
libsem.h - nagłówek biblioteki
Makefile

* Uruchamianie:
===============
Aby uruchomić program:
$ make run

Usuwanie plików *.o, *.x:
$ make clean

Pakowanie do archiwum:
$ make tar

* Treść zadania:
================
6) Przy pomocy semaforow nazwanych standardu POSIX zaimplementowac zadanie
wzajemnego wykluczania dla procesow podane w pseudokodzie na koncu podroz-
dzialu 5.1. Czas operacji na wspolnym zasobie symulowac uzywajac np. funkcji sleep. Dla
demonstracji poprawnosci dzialania programu uzyc odpowiednich komunikatow wypisy-
wanych przez poszczegolne procesy przed, w trakcie i po sekcji krytycznej oraz funkcji
podajacej wartosc semafora. Pamietac o zainicjowaniu semafora odpowiednia wartoscia
zaraz po jego utworzeniu.
• Stworzyc wlasna biblioteke prostych w uzyciu funkcji do tworzenia, otwierania, uzy-
skiwania wartosci, operowania, zamykania i usuwania semafora – korzystajacych z
odpowiednich funkcji systemowych/bibliotecznych i zawierajacych obsluge bledow.
Funkcje do tworzenia i otwierania semafora niech zwracaja jego adres w przypadku
sukcesu, a wskaznik NULL w przypadku bledu, natomiast pozostale funkcje niech w
przypadku sukcesu zwracaja wartosc 1, a w przypadku bledu wartosc 0. Wywolywac
te funkcje jako argumenty makra CheckError opisanego ponizej.
• Napisac specjalny program do powielania procesow realizujacych wzajemne wyklu-
czanie – w oparciu o funkcje fork i execlp (nazwe programu do inicjowania pro-
cesow, liczbe procesow oraz liczbe sekcji krytycznych/prywatnych kazdego procesu
przekazywac przez argumenty programu "powielacza"). Program ten powinien na
poczatku utworzyc i zainicjowac semafor, a na koncu – kiedy wszystkie jego procesy
potomne zakoncza swoje dzialanie – usunac go.
• Semafor usuwac w funkcji rejestrowanej przez funkcje atexit (zwrocic uwage, kiedy
nalezy wywolac funkcje exit, a kiedy exit). Dodac rowniez mozliwosc usuwania
semafora w funkcji obslugi sygnalu SIGINT, na wypadek gdyby program trzeba bylo
zakonczyc sekwencja klawiszy Ctrl-C (np. przez wywolanie exit(EXIT SUCCESS)
w funkcji obslugi sygnalu rejestrowanej przez signal).
• W celu weryfikacji poprawnosci wzajemnego wykluczania procesow niech program
"powielacz" na samym poczatku stworzy plik tekstowy numer.txt i wpisze w nim
numer o wartosci 0 (zero), a program implementujacy wzajemne wykluczanie w swo-
jej sekcji krytycznej odczytuje wartosc zapisanego w tym pliku numeru, nastepnie
zwieksza go o 1 i po losowej (np. funkcja rand) chwili czasu zapisuje z powrotem do
pliku. Po zakonczeniu dzialania wszystkich procesow realizujacych wzajemne wy-
kluczanie proces "powielacz" powinien sprawdzic poprawnosc koncowego numeru
zapisanego w pliku i wypisac odpowiedni komunikat.
! Sprawdzic, jaka bedzie koncowa wartosc numeru bez uzycia sekcji krytycznej.
