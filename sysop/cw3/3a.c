#define _GNU_SOURCE

#include "lib.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Mateusz Wojtyna                                                Kraków, 21.03.2025
// Napisac program do obslugi sygnalow z mozliwosciami: (1) wykonania operacji domy-
// slnej, (2) ignorowania oraz (3) przechwycenia i wlasnej obslugi sygnalu. Do ocze-
// kiwania na sygnal uzyc funkcji pause. Uruchamiac program i wysylac do niego
// sygnaly przy pomocy sekwencji klawiszy oraz przy pomocy polecenia kill z poziomu
// powloki.

void customHandler(int sig) {
    printf("Obsłużono sygnał - %s\n", strsignal(sig));
}

int main(int argc, char* argv[]) {
    Args args = handleArgs(argc, argv);

    typedef void (*sighandler_t)(int);
    sighandler_t handler;

    switch (args.op) {
        case 0: {
            handler = SIG_DFL;
            break;
        }
        case 1: {
            handler = SIG_IGN;
            break;
        }
        case 2: {
            handler = customHandler;
            break;
        }
    }

    if (signal(args.sig, handler) == SIG_ERR) {
        perror("signal() error");
        exit(1);
    }
    printf("PID: %d\n", getpid());

    //while (1) {
        pause();
    //}

    return 0;
}
