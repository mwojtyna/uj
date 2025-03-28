#define _GNU_SOURCE

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
    if (argc != 3) {
        printf("Niepoprawna liczba argumentów\n");
        printf("%s <nr_sygnału> <operacja>\n", argv[0]);
        printf("<operacja>:\n");
        printf(" - 0: operacja domyślna\n");
        printf(" - 1: zignorowanie sygnału\n");
        printf(" - 2: przechywcenie sygnału\n");
        exit(1);
    }

    int sig;
    int op;
    if (sscanf(argv[1], "%d", &sig) != 1) {
        printf("Niepoprawny nr sygnału: %s", argv[1]);
    }
    if (sscanf(argv[2], "%d", &op) != 1) {
        printf("Niepoprawny typ operacji: %s", argv[2]);
    }

    typedef void (*sighandler_t)(int);
    sighandler_t handler;

    switch (op) {
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
    default: {
        printf("Niepoprawny typ operacji: %s", argv[2]);
        exit(1);
    }
    }

    if (signal(sig, handler) == SIG_ERR) {
        perror("signal() error");
        exit(1);
    }
    printf("PID: %d\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}
