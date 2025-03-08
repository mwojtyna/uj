#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

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
