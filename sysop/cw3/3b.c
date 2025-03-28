#define _GNU_SOURCE

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Uruchomic powyzszy program poprzez funkcje execlp w procesie potomnym innego
// procesu (z uzyciem funkcji fork) i wysylac do niego sygnaly poprzez funkcje syste-
// mowa kill z procesu macierzystego. ! Uwaga: Przed wyslaniem sygnalu sprawdzic,
// na zakonczenie swojego potomka przy pomocy funkcji wait, a nastepnie wypisac
// czy proces istnieje (patrz podrozdzial 3.2). Proces macierzysty powinien zaczekac
// jego PID i status zakonczenia zwracane przez te funkcje. W przypadku zakonczenia
// procesu potomnego przez sygnal, powinien dodatkowo wypisac numer tego sygnalu
// zawarty w statusie zakonczenia, a takze jego nazwe (uzyc funkcji strsignal). Do
// wyluskania numeru sygnalu ze statusu zakonczenia uzyc makr opisanych w podroz-
// dziale 2.4.
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
    if (sscanf(argv[1], "%d", &sig) != 1) {
        printf("Niepoprawny nr sygnału: %s", argv[1]);
    }

    int childPid = fork();
    switch (childPid) {
        case -1:
            perror("fork() error");
            exit(1);
            break;

        // Potomek
        case 0:
            if (execlp("./3a.x", "./3a.x", argv[1], argv[2], NULL) == -1) {
                perror("execlp() error");
                _exit(1);
            }
            break;

        // Macierzysty
        default:
            sleep(1);

            // Sprawdź czy proces istneje
            if (kill(childPid, 0) == -1) {
                perror("kill() error");
                exit(1);
            }

            if (kill(childPid, sig) == -1) {
                perror("kill() error");
                exit(1);
            }

            int status;
            if (wait(&status) == -1) {
                perror("wait() error");
                exit(1);
            }

            if (WIFSIGNALED(status)) {
                int killedBy = WTERMSIG(status);
                printf("Proces potomny zabity przez %s", strsignal(killedBy));
            }
            break;
    }

    return 0;
}
