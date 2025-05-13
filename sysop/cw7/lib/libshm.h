#ifndef LIBSHM_H
#define LIBSHM_H

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// Mateusz Wojtyna                   13.05
// Biblioteka do obsługi pamięci dzielonej

/// Otwórz/stwórz obiekt pamięci dzielonej. Zwraca deskryptor lub -1 jeśli error.
int libshm_open(const char* name, int flags, mode_t mode);

/// Ustawia rozmiar obiektu pamięci dzielonej. Zwraca -1 jeśli error.
int libshm_set_size(int fd, off_t length);

/// Zamyka obiekt pamięci dzielonej. Zwraca -1 jeśli error.
int libshm_close(int fd);

/// Usuwa obiekt pamięci dzielonej. Zwraca -1 jeśli error.
int libshm_delete(const char* name);

#endif
