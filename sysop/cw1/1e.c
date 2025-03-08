#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

int main(void) {
    printProcessData("Rodzic");

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            // Potomek
            if (setpgid(0, 0) == -1) {
                perror("Błąd ustawiania PGID");
                exit(1);
            }
            printProcessData("Potomek");
        } else {
            if (wait(NULL) == -1) {
                perror("wait() error");
                exit(1);
            }
        }
    }

    return 0;
}
