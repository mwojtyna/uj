#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    printProcessData("Rodzic");

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            // Potomek
            sleep(3);
            printProcessData("Potomek");
        }
    }

    return 0;
}
