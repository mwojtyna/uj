========================================================================
Autor: Mateusz Wojtyna                                        24.05.2025
========================================================================

* Opis:
=======
Program realizujący kalkulator na podstawie kolejek komunikatów POSIX z serwerem obsługującym wiele klientów.

* Zawartość:
============
libmq.c - biblioteka 
libmq.h - nagłówek biblioteki
client.c - program klient
server.c - program server
Makefile

* Uruchamianie:
===============
Aby uruchomić serwer, klient1 oraz klient2 w wielu terminalach:
$ make run

Aby uruchomić tylko server:
$ make run_server

Aby uruchomić tylko klient:
$ make run_client

Usuwanie plików *.o, *.x:
$ make clean

Pakowanie do archiwum:
$ make tar

