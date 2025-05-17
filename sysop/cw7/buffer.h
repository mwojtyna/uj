#ifndef BUFFER_H
#define BUFFER_H

#define N_ELE 20 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define N_BUF 5  // Liczba elementow bufora

typedef struct {
    char element[N_ELE];
    int size;
} Towar;

typedef struct {
    Towar bufor[N_BUF];
    int wstaw;
    int wyjmij;
} SegmentPD;

#define SEM_WRITE "/sem_write"
#define SEM_READ "/sem_read"
#define SHM_NAME "/shared_buf"
#define SHM_SIZE sizeof(SegmentPD)

#endif
