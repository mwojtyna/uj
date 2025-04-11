#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

char* pipe_name = "EMPTY";
void delete_pipe(void) {
    fprintf(stderr, "Deleting pipe...\n");
    if (unlink(pipe_name) == -1) {
        perror("error deleting pipe while exiting");
        _exit(1);
    }
}
void delete_pipe_sig(int sig) {
    fprintf(stderr, "\nDeleting pipe...\n");
    if (unlink(pipe_name) == -1) {
        perror("error deleting pipe while exiting");
        _exit(1);
    }
    _exit(sig);
}

// Mateusz Wojtyna                                                   Kraków, 10.04
// 5a) Utworzyc potok FIFO z poziomu programu, a nastepnie uruchomic procesy Produ-
// centa i Konsumenta w tym samym programie (w procesie macierzystym i potomnym
// lub w dwoch potomnych). Potok usuwac w funkcji zarejestrowanej przez atexit.
int main(int argc, char* argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr,
                "%s <potok> <program_producent> <program_konsument> <plik_wejsciowy> "
                "<plik_wyjsciowy>\n",
                argv[0]);
        exit(1);
    }
    pipe_name = argv[1];
    char* prod_exe = argv[2];
    char* kons_exe = argv[3];
    char* infile_name = argv[4];
    char* outfile_name = argv[5];

    if (mkfifo(pipe_name, 0644) == -1) {
        perror("mkfifo error");
        exit(1);
    }

    if (atexit(delete_pipe) == -1) {
        perror("atexit error");
        exit(1);
    }
    if (signal(SIGINT, delete_pipe_sig) == SIG_ERR) {
        perror("error setting SIGINT handler");
        exit(1);
    }

    switch (fork()) {
        case -1:
            perror("fork 1 error");
            exit(1);

        case 0:
            // Producent
            if (execlp(prod_exe, prod_exe, pipe_name, infile_name, NULL) == -1) {
                perror("error executing producer");
                _exit(1);
            }
            exit(0);
    }
    switch (fork()) {
        case -1:
            perror("fork 2 error");
            exit(1);

        case 0:
            // Konsument
            if (execlp(kons_exe, kons_exe, pipe_name, outfile_name, NULL) == -1) {
                perror("error executing consumer");
                _exit(1);
            }
            exit(0);
    }

    if (wait(NULL) == -1) {
        perror("wait error");
        exit(1);
    }
    if (wait(NULL) == -1) {
        perror("wait error");
        exit(1);
    }

    return 0;
}
