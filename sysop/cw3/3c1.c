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
    signal(args.sig, SIG_IGN);

    for (int i = 0; i < N; ++i) {
        switch (fork()) {
            case -1:
                perror("child fork() error");
                _exit(1);

            case 0:
                execlp("./3a.x", "./3a.x", argv[1], argv[2], NULL);
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
            int exitStatus = WEXITSTATUS(status);
            printf("Proces potomny o PID=%d zabity (status=%d) przez sygnał "
                   "%d (%s)\n",
                   killedPid, exitStatus, killedBy, strsignal(killedBy));
        } else {
            int exitStatus = WEXITSTATUS(status);
            printf("Proces potomny o PID=%d się zakończył (status=%d)\n",
                   killedPid, exitStatus);
        }
    }

    return 0;
}
