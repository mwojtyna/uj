#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

void printProcessData(char* name) {
    uid_t uid = getuid();
    gid_t gid = getgid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgrp();

    printf("%s: UID=%u, GID=%u, PID=%u, PPID=%u, PGID=%u\n", name, uid, gid,
           pid, ppid, pgid);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Wymagana jest ścieżka programu do uruchomienia w potomku!");
        exit(1);
    }

    printProcessData("Rodzic");

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            // Potomek
            if (execlp(argv[1], argv[1], NULL) == -1) {
                perror("execlp error");
            }
        }
    }

    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}
