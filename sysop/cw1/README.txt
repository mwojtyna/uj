========================================================================
Autor: Mateusz Wojtyna                                Krakow, ??.03.2025
========================================================================

* Zawartość:
============
1a.c - program z podpunktu (a) 
1b.c - program z podpunktu (b) 
1c.c - program z podpunktu (c) 
1d.c - program z podpunktu (d) 
1e.c - program z podpunktu (e) 
lib.c, lib.h - biblioteka z funkcjami dzielonymi przez kilka programów
odpowiedzi.txt - odpowiedzi na dodatkowe pytania

* Uruchamianie:
===============
Aby uruchomić poszczególne programy:
$ make
$ ./1a.x
$ ./1b.x
...

Usuwanie plików *.o, *.x:
$ make clean

* Treść zadania:
================

(a) Napisac program wypisujacy identyfikatory UID, GID, PID, PPID i PGID dla da-
nego procesu.

(b) Wywolac funkcje fork trzy razy (najlepiej w petli for) i wypisac powyzsze iden-
tyfikatory dla procesu macierzystego oraz wszystkich procesow potomnych (najle-
piej dla kazdego procesu w pojedynczej linii). Przy pomocy funkcji wait sprawic,
aby proces macierzysty zaczekal na zakonczenie wszystkich procesow potomnych.

(c) Jak w (b), tylko przy uzyciu funkcji sleep (! nie uzywac funkcji wait) sprawiac
by procesy potomne byly adoptowane przez proces init lub jego odpowiednik.
Nastepnie z poziomu powloki wykonac polecenie pstree -p i w wyswietlonym
drzewie procesow zidentyfikowac proces, ktory adoptuje osierocone procesy w
danym systemie.

(d) Jak w (b), tylko wstawic funkcje sleep w takich miejscach programu, aby
procesy pojawialy sie na ekranie grupowane pokoleniami od najstarszego do
najmlodszego, a proces macierzysty konczyl sie dopiero po procesach potom-
nych (nie uzywac funkcji wait). Na podstawie wynikow programu sporzadzic
"drzewo genealogiczne" tworzonych procesow, tzn. do pliku tekstowego,wkleic”
wyniki programu, a nastepnie narysowac drzewo genealogiczne, zaznaczajac na
nim identyfikatory PID, PPID i PGID.

(e) Jak w (b), tylko przy uzyciu fukcji setpgid sprawic by kazdy proces potomny
stawal sie liderem swojej wlasnej grupy procesow.

Ile procesow powstanie przy n-krotnym wywolaniu funkcji fork i dlaczego?
