#include "buffer.h"
#include "lib/sem.h"
#include "lib/shm.h"
#include "utils.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr,
                "%s <semafor_read> <semafor_write> <nazwa_pamieci_dzielonej> <plik_wejsciowy> "
                "<plik_wyjsciowy>\n",
                argv[0]);
        exit(1);
    }
    char* sem_read_name = argv[1];
    char* sem_write_name = argv[2];
    char* shm_name = argv[3];
    char* infile_name = argv[4];
    char* outfile_name = argv[5];

    int shm_fd = libshm_open(shm_name, O_RDWR, 0666);
    CheckError(shm_fd != -1);
    void* buf_addr = libshm_map(shm_fd, SHM_SIZE);
    CheckError(buf_addr != NULL);
    SegmentPD* buf = (SegmentPD*)buf_addr;

    sem_t* sem_read = libsem_open(sem_read_name);
    sem_t* sem_write = libsem_open(sem_write_name);
    CheckError(sem_read != NULL);
    CheckError(sem_write != NULL);

    Towar towar;
    int counter = 1;

    while (counter <= N_TOWAR) {
        CheckError(libsem_wait(sem_read));

        towar = buf->bufor[buf->wyjmij];
        int sem_val;
        libsem_get_value(sem_read, &sem_val);
        printf("[KONSUMENT] Odbieram towar '%s' (index=%d, sem=%d, bytes=%d)\n", towar.element,
               buf->wyjmij, sem_val, N_ELE);

        buf->wyjmij = (buf->wyjmij + 1) % N_BUF;
        CheckError(libsem_post(sem_write));

        counter++;
        sleep(1);
    }

    CheckError(libsem_close(sem_write));
    CheckError(libsem_close(sem_read));
    CheckError(libshm_unmap(buf_addr, SHM_SIZE));
    CheckError(libshm_close(shm_fd));

    return 0;
}
