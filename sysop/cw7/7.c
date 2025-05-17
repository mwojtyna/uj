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

// Mateusz Wojtyna      17.05
// Program realizujący problem producenta-konsumenta za pomocą bufora cyklicznego.
// Dostęp do bufora synchronizowany przez semafory.

void cleanup(void) {
    CheckError(libsem_delete(SEM_PROD));
    CheckError(libsem_delete(SEM_KONS));
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
    char* infile_name = argv[3];
    char* outfile_name = argv[4];

    int shm_fd = libshm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    CheckError(shm_fd != -1);
    CheckError(libshm_set_size(shm_fd, SHM_SIZE));
    void* buf_addr = libshm_map(shm_fd, SHM_SIZE);
    CheckError(buf_addr != NULL);

    SegmentPD* buf = (SegmentPD*)buf_addr;
    buf->wstaw = 0;
    buf->wyjmij = 0;

    sem_t* sem_kons = libsem_init(SEM_KONS, 0);
    void* sem_prod = libsem_init(SEM_PROD, N_BUF);
    CheckError(sem_kons != NULL);
    CheckError(sem_prod != NULL);

    int kons_val;
    int prod_val;
    CheckError(libsem_get_value(sem_kons, &kons_val));
    CheckError(libsem_get_value(sem_prod, &prod_val));
    printf("semafor konsumenta: adres=%p, wartość=%d\n", (void*)sem_kons, kons_val);
    printf("semafor producenta: adres=%p, wartość=%d\n", (void*)sem_prod, prod_val);
    printf("pamięć dzielona: deskryptor=%d\n\n", shm_fd);

    switch (fork()) {
        case -1:
            perror("fork error");
            exit(1);

        case 0:
            if (execlp(prod_exe, prod_exe, SEM_KONS, SEM_PROD, SHM_NAME, infile_name, NULL) == -1) {
                perror("fork producer error");
                _exit(1);
            }
    }
    switch (fork()) {
        case -1:
            perror("fork error");
            exit(1);

        case 0:
            if (execlp(kons_exe, kons_exe, SEM_KONS, SEM_PROD, SHM_NAME, outfile_name, NULL) ==
                -1) {
                perror("fork consument error");
                _exit(1);
            }
    }

    CheckError(wait(NULL) != -1);
    CheckError(wait(NULL) != -1);

    return 0;
}
