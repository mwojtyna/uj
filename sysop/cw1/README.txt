========================================================================
Autor: Mateusz Wojtyna                                        08.03.2025
========================================================================

* Zawartość:
============
1a.c - kod programu 1, podpunkt a 
1b.c - kod programu 1, podpunkt b 
1c.c - kod programu 1, podpunkt c 
1d.c - kod programu 1, podpunkt d 
1e.c - kod programu 1, podpunkt e 
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

Pakowanie do archiwum:
$ make tar

* Treść zadania:
================
1.a Napisac program wypisujacy identyfikatory UID, GID, PID, PPID i PGID dla da-
nego procesu.

1.b Wywolac funkcje fork trzy razy (najlepiej w petli for) i wypisac powyzsze iden-
tyfikatory dla procesu macierzystego oraz wszystkich procesow potomnych (najle-
piej dla kazdego procesu w pojedynczej linii). Przy pomocy funkcji wait sprawic,
aby proces macierzysty zaczekal na zakonczenie wszystkich procesow potomnych.

1.c Jak w b, tylko przy uzyciu funkcji sleep (! nie uzywac funkcji wait) sprawiac
by procesy potomne byly adoptowane przez proces init lub jego odpowiednik.
Nastepnie z poziomu powloki wykonac polecenie pstree -p i w wyswietlonym
drzewie procesow zidentyfikowac proces, ktory adoptuje osierocone procesy w
danym systemie.

1.d Jak w b, tylko wstawic funkcje sleep w takich miejscach programu, aby
procesy pojawialy sie na ekranie grupowane pokoleniami od najstarszego do
najmlodszego, a proces macierzysty konczyl sie dopiero po procesach potom-
nych (nie uzywac funkcji wait). Na podstawie wynikow programu sporzadzic
"drzewo genealogiczne" tworzonych procesow, tzn. do pliku tekstowego,wkleic”
wyniki programu, a nastepnie narysowac drzewo genealogiczne, zaznaczajac na
nim identyfikatory PID, PPID i PGID.

1.e Jak w b, tylko przy uzyciu fukcji setpgid sprawic by kazdy proces potomny
stawal sie liderem swojej wlasnej grupy procesow.

Ile procesow powstanie przy n-krotnym wywolaniu funkcji fork i dlaczego?
