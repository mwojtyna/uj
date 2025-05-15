#ifndef SEM_H
#define SEM_H

#include <semaphore.h>

// Mateusz Wojtyna           29.04
// Biblioteka do obsługi semaforów

#define FILE_NAME "numer.txt"

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
int libsem_delete(const char* name);

// Wstrzymuje proces aż do momentu, gdy semafor będzie miał wartość większą od 0
// Error: zwraca 0
int libsem_wait(sem_t* sem);

// Jeżeli istnieją procesy wstrzymane pod semaforem, to wywołanie funkcji spowoduje uruchomienie jednego z nich
// Error: zwraca 0
int libsem_post(sem_t* sem);

#endif
