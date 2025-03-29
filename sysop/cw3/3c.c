#define _GNU_SOURCE

#include "lib.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Mateusz Wojtyna                                                          29.03.2025
// 3c. W procesie macierzystym utworzyc proces potomny (funkcja fork) i sprawic, aby stal
// sie liderem nowej grupy procesow (funkcja setpgid), a nastepnie poprzez funkcje
// execlp uruchomic w nim program tworzacy kilka procesow potomnych (funkcja fork
// w petli), ktore poprzez funkcje execlp wykonuja program do obslugi sygnalow z
// punktu (a). Z pierwszego procesu macierzystego wysylac sygnaly do calej grupy
// procesow potomnych po uprzednim sprawdzeniu jej istnienia. Identyfikator tej
// grupy procesow uzyskac przy pomocy funkcji getpgid. Proces bedacy liderem grupy
// procesow niech ignoruje sygnaly, a na koncu czeka na zakonczenie wszystkich swo-
// ich procesow potomnych i wypisuje ich identyfikatory PID oraz status zakonczenia
// (zwracane przez funkcje wait), a w przypadku zakonczenia tych procesow przez
// sygnal, takze numer i nazwe odpowiedniego sygnalu. Pierwszy proces macierzy-
// sty rowniez powinien zaczekac na zakonczenie swojego bezposredniego potomka i
// wypisac jego PID oraz status zakonczenia zwracane przez funkcje wait.
//
// Numer sygnalu oraz opcje jego obslugi we wszystkich powyzszych programach przeka-
// zywac za pomoca argumentow wywolania programu – sprawdzac ich liczbe i wypisywac
// odpowiedni komunikat w przypadku blednego uruchomienia (ze wskazowka jak poprawnie
// uruchomic program).
int main(int argc, char* argv[]) {
    Args args = handleArgs(argc, argv);

    pid_t childPid = fork();
    switch (childPid) {
        case -1:
            perror("fork() error");

        case 0:
            // Potomek
            if (setpgid(0, 0) == -1) {
                perror("setpgrp() error");
                _exit(1);
            }

            if (execlp("./3c1.x", "./3c1.x", argv[1], argv[2], NULL) == -1) {
                perror("execlp() error");
                _exit(1);
            }
            break;

        default:
            // Macierzysty

            // Musimy poczekać aż proces potomny zostanie liderem grupy
            sleep(1);

            pid_t childGroupId = getpgid(childPid);
            if (childGroupId == -1) {
                perror("getpgid() error");
                exit(1);
            }

            // Sprawdź czy proces istneje
            if (kill(-childGroupId, 0) == -1) {
                perror("kill() error");
                exit(1);
            }
            if (kill(-childGroupId, args.sig) == -1) {
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
                printf("Pierwszy potomek o PID=%d zabity (status=%d) przez %d "
                       "(%s) \n",
                       childPid, exitStatus, killedBy, strsignal(killedBy));
            } else {
                int exitStatus = WEXITSTATUS(status);
                printf("Pierwszy potomek o PID=%d się zakończył (status=%d)\n",
                       childPid, exitStatus);
            }
            break;
    }

    return 0;
}
