#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Mateusz Wojtyna
// Proces macierzysty od razy po utworzeniu potomków kończy się,
// potomkowie są adoptowani przez proces init/systemd
int main(void) {
    printf("Poczekaj aż wypiszą się wszystkie komunikaty...\n");
    printProcessData("Rodzic");

    int gen = 0;
    for (int i = 0; i < 3; i++) {
        switch (fork()) {
            case -1: {
                perror("Fork error");
                exit(1);
            }
            case 0: {
                // Potomek
                gen++;
                sleep(3); // 3 sekundy żebym miał czas na uruchomienie `pstree`
                printProcessData("Potomek");
                break;
            }
        }
    }

    if (gen == 0) {
        printf("Rodzic się zakończył, zaraz wypiszą się dane potomków "
               "adoptowanych przez init/systemd\n");
    }

    return 0;
}
