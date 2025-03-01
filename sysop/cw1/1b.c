#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    printf("Rodzic:\n");
    printProcessData();

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            // Potomek
            printf("\nPotomek %d:\n", i + 1);
            printProcessData();
            exit(0);
        }

        // Gdy jest rodzicem, kontynuujemy pętlę
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
