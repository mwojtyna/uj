#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

int main(void) {
    printProcessData("Rodzic");

    int gen = 0;
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            // Potomek
            sleep(gen);
            gen++;

            char name[64];
            sprintf(name, "Potomek poziomu %d", gen);
            printProcessData(name);
        }
    }

    sleep(N + 1);
    return 0;
}
