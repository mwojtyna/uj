#include "buffer.h"
#include "lib/sem.h"
#include "lib/shm.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Mateusz Wojtyna      Kraków, 17.05
// KONSUMENT
int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr,
                "%s <semafor_kons> <semafor_prod> <nazwa_pamieci_dzielonej> <plik_wyjsciowy>\n",
                argv[0]);
        exit(1);
    }
    char* sem_kons_name = argv[1];
    char* sem_prod_name = argv[2];
    char* shm_name = argv[3];
    char* outfile_name = argv[4];

    srand(time(NULL));

    int outfile_fd = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    CheckError(outfile_fd != -1);

    int shm_fd = libshm_open(shm_name, O_RDWR, 0666);
    CheckError(shm_fd != -1);
    void* buf_addr = libshm_map(shm_fd, SHM_SIZE);
    CheckError(buf_addr != NULL);
    SegmentPD* buf = (SegmentPD*)buf_addr;

    sem_t* sem_kons = libsem_open(sem_kons_name);
    sem_t* sem_prod = libsem_open(sem_prod_name);
    CheckError(sem_prod != NULL);
    CheckError(sem_kons != NULL);

    int kons_val;
    int prod_val;
    CheckError(libsem_get_value(sem_kons, &kons_val));
    CheckError(libsem_get_value(sem_prod, &prod_val));
    printf("[KONSUMENT] semafor konsumenta: adres=%p, wartość=%d\n", (void*)sem_kons, kons_val);
    printf("[KONSUMENT] semafor producenta: adres=%p, wartość=%d\n", (void*)sem_prod, prod_val);
    printf("[KONSUMENT] pamięć dzielona: deskryptor=%d\n", shm_fd);

    while (1) {
        CheckError(libsem_wait(sem_kons));
        {
            Towar towar = buf->bufor[buf->wyjmij];

            int sem_val;
            CheckError(libsem_get_value(sem_kons, &sem_val));
            printf("[KONSUMENT] Odbieram towar '%s' (index=%d, sem=%d, bytes=%d)\n", towar.element,
                   buf->wyjmij, sem_val, towar.size);

            CheckError((write(outfile_fd, towar.element, towar.size)) != -1);

            buf->wyjmij = (buf->wyjmij + 1) % N_BUF;

            // Zakończ pętlę jeśli koniec danych
            if (towar.size > 0 && towar.size < N_ELE && towar.element[towar.size] == '\0') {
                CheckError(libsem_post(sem_prod));
                break;
            }
        }
        CheckError(libsem_post(sem_prod));

        sleep(rand() % 2);
    }

    CheckError(libsem_close(sem_prod));
    CheckError(libsem_close(sem_kons));
    CheckError(libshm_unmap(buf_addr, SHM_SIZE));
    CheckError(libshm_close(shm_fd));

    return 0;
}
