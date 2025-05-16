#include "buffer.h"
#include "lib/sem.h"
#include "lib/shm.h"
#include "utils.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int shm_fd = libshm_open(SHM_NAME, O_RDWR, 0666);
    CheckError(shm_fd != -1);
    void* buf_addr = libshm_map(shm_fd, SHM_SIZE);
    CheckError(buf_addr != NULL);
    SegmentPD* buf = (SegmentPD*)buf_addr;

    sem_t* sem_read = libsem_open(SEM_READ);
    sem_t* sem_write = libsem_open(SEM_WRITE);
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
