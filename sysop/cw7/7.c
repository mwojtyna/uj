#include "buffer.h"
#include "lib/sem.h"
#include "lib/shm.h"
#include "utils.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void cleanup() {
    CheckError(libsem_delete(SEM_WRITE));
    CheckError(libsem_delete(SEM_READ));
    CheckError(libshm_delete(SHM_NAME));
}

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\nCleaning up...\n");
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    CheckError(atexit(cleanup) == 0);
    CheckError(signal(SIGINT, signal_handler) != SIG_ERR);

    if (argc != 5) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr,
                "%s <program_producent> <program_konsument> <plik_wejsciowy> <plik_wyjsciowy>\n",
                argv[0]);
        exit(1);
    }
    char* prod_exe = argv[1];
    char* kons_exe = argv[2];

    int shm_fd;
    void* buf_addr;
    sem_t* sem_read;
    sem_t* sem_write;

    CheckError((shm_fd = libshm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666)) != -1);
    CheckError(libshm_set_size(shm_fd, SHM_SIZE));
    CheckError((buf_addr = libshm_map(shm_fd, SHM_SIZE)) != NULL);

    SegmentPD* buf = (SegmentPD*)buf_addr;
    buf->wstaw = 0;
    buf->wyjmij = 0;

    CheckError(sem_read = libsem_init(SEM_READ, N_BUF));
    CheckError(sem_write = libsem_init(SEM_WRITE, 0));

    switch (fork()) {
        case -1:
            perror("fork error");
            exit(1);

        case 0:
            if (execlp(prod_exe, prod_exe, NULL) == -1) {
                perror("fork prod error");
                _exit(1);
            }
    }
    switch (fork()) {
        case -1:
            perror("fork error");
            exit(1);

        case 0:
            if (execlp(kons_exe, kons_exe, NULL) == -1) {
                perror("fork kons error");
                _exit(1);
            }
    }

    CheckError(wait(NULL) != -1);
    CheckError(wait(NULL) != -1);

    return 0;
}
