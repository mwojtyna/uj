#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

// Mateusz Wojtyna
// Wypisuje pokolenia procesów od najstarszego do najmłodszego
int main(void) {
    printProcessData("Rodzic");

    int gen = 0;
    for (int i = 0; i < N; i++) {
        switch (fork()) {
        case -1: {
            perror("Fork error");
            exit(1);
        }
        case 0: {
            // Potomek
            sleep(gen);
            gen++;

            char name[64];
            sprintf(name, "Potomek poziomu %d", gen);
            printProcessData(name);
            break;
        }
        }
    }

    sleep(N + 1);
    return 0;
}
