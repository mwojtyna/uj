#define _GNU_SOURCE

#include "lib.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

// Mateusz Wojtyna                      29.03.2025
// Pomocnik do 3c, tworzy kilka procesów potomnych
int main(int argc, char* argv[]) {
    Args args = handleArgs(argc, argv);
    if(signal(args.sig, SIG_IGN) == SIG_ERR) {
        perror("signal() error");
        exit(1);
    }

    for (int i = 0; i < N; ++i) {
        switch (fork()) {
            case -1:
                perror("child fork() error");
                _exit(1);

            case 0:
                if(execlp("./3a.x", "./3a.x", argv[1], argv[2], NULL) == -1) {
                    perror("execlp() error");
                    _exit(1);
                }
                break;
        }
    }

    for (int i = 0; i < N; ++i) {
        int status;
        pid_t killedPid = wait(&status);
        if (killedPid == -1) {
            perror("wait() error");
            exit(1);
        }
        if (WIFSIGNALED(status)) {
            int killedBy = WTERMSIG(status);
            printf("Proces potomny o PID=%d zabity (status=%d) przez sygnał "
                   "%d (%s)\n",
                   killedPid, status, killedBy, strsignal(killedBy));
        } else {
            printf("Proces potomny o PID=%d się zakończył (status=%d)\n",
                   killedPid, status);
        }
    }

    return 0;
}
