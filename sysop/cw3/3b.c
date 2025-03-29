#define _GNU_SOURCE

#include "lib.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Mateusz Wojtyna                                                          29.03.2025
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
    Args args = handleArgs(argc, argv);

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

            if (kill(childPid, args.sig) == -1) {
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
                int exitStatus = WEXITSTATUS(status);
                printf("Proces potomny o PID=%d zabity (status=%d) przez %d "
                       "(%s)\n",
                       childPid, exitStatus, killedBy, strsignal(killedBy));
            } else {
                int exitStatus = WEXITSTATUS(status);
                printf("Proces potomny o PID=%d zabity (status=%d)\n", childPid,
                       exitStatus);
            }
            break;
    }

    return 0;
}
