#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

// Funkcja pomocnicza do wyświetlania danych procesu
void printProcessData(char* name) {
    uid_t uid = getuid();
    gid_t gid = getgid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgrp();

    printf("%s: UID=%u, GID=%u, PID=%u, PPID=%u, PGID=%u\n", name, uid, gid,
           pid, ppid, pgid);
}

// Mateusz Wojtyna
// Dla każdego procesu potomnego, uruchamia program podany w argumencie i przekazuje mu treść do wyświetlenia
int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Wymagana jest ścieżka programu do uruchomienia w potomku!\n");
        exit(1);
    }

    printProcessData("Rodzic");

    for (int i = 0; i < N; i++) {
        switch (fork()) {
            case -1: {
                perror("Fork error");
                exit(1);
            }
            case 0: {
                uid_t uid = getuid();
                gid_t gid = getgid();
                pid_t pid = getpid();
                pid_t ppid = getppid();
                pid_t pgid = getpgrp();

                char text[128];
                sprintf(text,
                        "Potomek: UID=%u, GID=%u, PID=%u, PPID=%u, PGID=%u",
                        uid, gid, pid, ppid, pgid);

                if (execlp(argv[1], argv[1], text, NULL) == -1) {
                    perror("execlp error");
                }
                break;
            }
            default: {
                if (wait(NULL) == -1) {
                    perror("wait() error");
                    exit(1);
                }
                break;
            }
        }
    }

    return 0;
}
