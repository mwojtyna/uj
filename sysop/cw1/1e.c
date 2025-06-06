#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

// Mateusz Wojtyna
// Każdy proces potomny staje się liderem grupy procesów
int main(void) {
    printProcessData("Rodzic");

    for (int i = 0; i < N; i++) {
        switch (fork()) {
            case -1: {
                perror("Fork error");
                exit(1);
            }
            case 0: {
                // Potomek
                if (setpgid(0, 0) == -1) {
                    perror("Błąd ustawiania PGID");
                    exit(1);
                }
                printProcessData("Potomek");
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
