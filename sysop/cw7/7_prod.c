#include "buffer.h"
#include "lib/sem.h"
#include "lib/shm.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Mateusz Wojtyna      Kraków, 17.05
// PRODUCENT
int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr,
                "%s <semafor_read> <semafor_write> <nazwa_pamieci_dzielonej> <plik_wejsciowy>\n",
                argv[0]);
        exit(1);
    }
    char* sem_read_name = argv[1];
    char* sem_write_name = argv[2];
    char* shm_name = argv[3];
    char* infile_name = argv[4];

    srand(time(NULL));

    int infile_fd = open(infile_name, O_RDONLY);
    CheckError(infile_fd != -1);

    int shm_fd = libshm_open(shm_name, O_RDWR, 0666);
    CheckError(shm_fd != -1);
    void* buf_addr = libshm_map(shm_fd, SHM_SIZE);
    CheckError(buf_addr != NULL);
    SegmentPD* buf = (SegmentPD*)buf_addr;

    sem_t* sem_read = libsem_open(sem_read_name);
    sem_t* sem_write = libsem_open(sem_write_name);
    CheckError(sem_read);
    CheckError(sem_write);

    Towar towar;
    int bytes;
    while ((bytes = read(infile_fd, towar.element, N_ELE)) != 0) {
        if (bytes == -1) {
            perror("[PRODUCENT] error reading input file");
            exit(1);
        }
        towar.size = bytes;

        CheckError(libsem_wait(sem_write));
        {
            buf->bufor[buf->wstaw] = towar;

            int sem_val;
            CheckError(libsem_get_value(sem_write, &sem_val));
            printf("[PRODUCENT] Wstawiam towar '%s' (index=%d, sem=%d, bytes=%d)\n", towar.element,
                   buf->wstaw, sem_val, N_ELE);

            // Jeżeli koniec pliku, to wstaw zakończ towar specjalnym znakiem
            if (towar.size > 0 && towar.size < N_ELE) {
                towar.element[towar.size] = '\0';
                buf->bufor[buf->wstaw] = towar;
            }

            buf->wstaw = (buf->wstaw + 1) % N_BUF;
        }
        CheckError(libsem_post(sem_read));

        sleep(rand() % 3);
    }

    CheckError(libsem_close(sem_write));
    CheckError(libsem_close(sem_read));
    CheckError(libshm_unmap(buf_addr, SHM_SIZE));
    CheckError(libshm_close(shm_fd));

    return 0;
}
