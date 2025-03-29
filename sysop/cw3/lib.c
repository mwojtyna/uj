#include "lib.h"

Args handleArgs(int argc, char* argv[]) {
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
        printf("Niepoprawny nr sygnału: %s\n", argv[1]);
        exit(1);
    }
    if (sig == 9 || sig == 19) {
        printf("Sygnału %d nie można obsłużyć\n", sig);
        exit(1);
    }
    if (sscanf(argv[2], "%d", &op) != 1 || !(op >= 0 && op <= 2)) {
        printf("Niepoprawny typ operacji: %s\n", argv[2]);
        exit(1);
    }

    Args args = {.sig = sig, .op = op};
    return args;
}
