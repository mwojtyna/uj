#include "libsem.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEM_NAME "/sem"

void cleanup(void) {
    if (libsem_unlink(SEM_NAME) == -1) {
        perror("Error deleting semaphor");
        _exit(1);
    }
}

void sig_cleanup(int sig) {
    if (sig == SIGINT) {
        printf("\nUsuwanie semaforu...\n");
        cleanup();
        _exit(1);
    }
}

// Mateusz Wojtyna          29.04
// Program do powielania procesów
int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr, "%s <worker> <liczba_procesow> <liczba_sekcji_krytycznych>\n", argv[0]);
        exit(1);
    }

    CheckError(atexit(cleanup) != -1);
    if (signal(SIGINT, sig_cleanup) == SIG_ERR) {
        perror("signal error");
        exit(1);
    }

    char* worker_name = argv[1];
    char* process_num_s = argv[2];
    char* critical_sections_s = argv[3];
    int process_num = atoi(process_num_s);
    int critical_sections = atoi(critical_sections_s);

    // Otwórz semafor i wypisz informacje
    sem_t* sem = libsem_init(SEM_NAME, 1);
    CheckError(sem != NULL);
    int svalue;
    CheckError(libsem_get_value(sem, &svalue) != 0);
    printf("Otwarto semafor z wartością %d, adresem %p\n", svalue, (void*)sem);

    // Otwórz plik i wpisz "0"
    int num_fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    CheckError(num_fd != -1);
    char* write_buf = "0";
    CheckError(write(num_fd, write_buf, strlen(write_buf)));
    CheckError(close(num_fd) != -1);

    for (int i = 0; i < process_num; i++) {
        switch (fork()) {
            case -1:
                perror("fork error");
                exit(1);

            case 0:
                if (execlp(worker_name, worker_name, SEM_NAME, critical_sections_s, NULL) == -1) {
                    perror("execlp error");
                    _exit(1);
                }
        }
    }
    for (int i = 0; i < process_num; i++) {
        CheckError(wait(NULL) != -1);
    }

    // Otwórz plik i wczytaj zawartość
    num_fd = open(FILE_NAME, O_RDONLY, 0644);
    CheckError(num_fd != -1);
    char read_buf[8];
    ssize_t bytes = read(num_fd, read_buf, sizeof(read_buf) - 1);
    CheckError(bytes != -1);
    read_buf[bytes] = '\0';

    CheckError(close(num_fd) != -1);

    // Porównaj faktyczną zawartość z oczekiwaną
    int final = atoi(read_buf);
    int expected = critical_sections * process_num;

    if (final == expected) {
        printf("OK! Oczekiwano: %d, otrzymano: %d\n", expected, final);
    } else {
        printf("ŹLE! Oczekiwano: %d, otrzymano: %d\n", expected, final);
    }

    return 0;
}
