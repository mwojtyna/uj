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
    CheckError(sem_read);
    CheckError(sem_write);

    Towar towar;
    int counter = 1;

    while (counter <= N_TOWAR) {
        snprintf(towar.element, N_ELE, "Towar %d", counter);
        CheckError(libsem_wait(sem_write));

        buf->bufor[buf->wstaw] = towar;
        int sem_val;
        libsem_get_value(sem_write, &sem_val);
        printf("[PRODUCENT] Wstawiam towar '%s' (index=%d, sem=%d, bytes=%d)\n", towar.element,
               buf->wstaw, sem_val, N_ELE);

        buf->wstaw = (buf->wstaw + 1) % N_BUF;
        CheckError(libsem_post(sem_read));

        counter++;
        sleep(1);
    }

    CheckError(libsem_close(sem_write));
    CheckError(libsem_close(sem_read));
    CheckError(libshm_unmap(buf_addr, SHM_SIZE));
    CheckError(libshm_close(shm_fd));

    return 0;
}
