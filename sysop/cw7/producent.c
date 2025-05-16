#include "buffer.h"
#include "lib/sem.h"
#include "lib/shm.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int shm_fd = libshm_open(SHM_NAME, O_RDWR, 0666);
    CheckError(shm_fd != -1);
    void* buf_addr = libshm_map(shm_fd, SHM_SIZE);
    CheckError(buf_addr != NULL);
    SegmentPD* buf = (SegmentPD*)buf_addr;

    sem_t* sem_read = libsem_open(SEM_READ);
    CheckError(sem_read);
    sem_t* sem_write = libsem_open(SEM_WRITE);
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
