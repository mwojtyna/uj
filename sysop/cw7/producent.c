#include "buffer.h"
#include "lib/sem.h"
#include "lib/shm.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int shm_fd;
    void* buf_addr;
    SegmentPD* buf;

    CheckError((shm_fd = libshm_open(SHM_NAME, O_RDWR, 0666)) != -1);
    CheckError((buf_addr = libshm_map(shm_fd, SHM_SIZE)) != NULL);
    buf = (SegmentPD*)buf_addr;

    sem_t* sem_read;
    sem_t* sem_write;
    CheckError(sem_read = libsem_open(SEM_READ));
    CheckError(sem_write = libsem_open(SEM_WRITE));

    Towar towar;
    int counter = 1;

    while (counter <= N_TOWAR) {
        snprintf(towar.element, N_ELE, "Towar %d", counter);
        CheckError(libsem_wait(sem_write));

        buf->bufor[buf->wstaw] = towar;
        printf("[PRODUCENT] Wstawiam towar '%s' (index %d)\n", towar.element, buf->wstaw);

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
