#ifndef LIBSEM_H
#define LIBSEM_H

#include <semaphore.h>

/*
=======================================================
Makro CheckError: wskaz lokalizacje bledu, wypisz nazwe
przekazywanego argumentu (#Arg) i zakoncz program.
=======================================================
*/
#define CheckError(Arg)                                                                            \
    if (!(Arg)) {                                                                                  \
        fprintf(stderr, "[ERROR] %s:%d (%s) -> CheckError argument: %s\n", __FILE__, __LINE__,     \
                __func__, #Arg);                                                                   \
        exit(EXIT_FAILURE);                                                                        \
    }

#endif

// Stwórz semafor
// Error: zwraca NULL
sem_t* libsem_init(const char* name, int value);

// Otwórz semafor
// Error: zwraca NULL
sem_t* libsem_open(const char* name);

// Zwraca wartość z semafora do podanego adresu
// Error: zwraca 0
int libsem_get_value(sem_t* sem, int* value);

// Zamyka semafor
// Error: zwraca 0
int libsem_close(sem_t* sem);

// Usuwa semafor
// Error: zwraca 0
int libsem_unlink(const char* name);
