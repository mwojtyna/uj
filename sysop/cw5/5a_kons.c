#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE_K 80

// Mateusz Wojtyna                              Kraków, 10.04
// KONSUMENT
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr, "%s <potok> <plik_wyjsciowy>\n", argv[0]);
        exit(1);
    }
    char* pipe_name = argv[1];
    char* outfile_name = argv[2];

    srand(time(NULL));

    int pipe_fd = open(pipe_name, O_RDONLY);
    if (pipe_fd == -1) {
        perror(">>> [KONSUMENT]: open pipe error");
        exit(1);
    }

    int outfile_fd = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd == -1) {
        perror(">>> [KONSUMENT]: open outfile error");
        exit(1);
    }

    char buf[BUF_SIZE_K];
    int bytes;
    while ((bytes = read(pipe_fd, buf, BUF_SIZE_K)) != 0) {
        if (bytes == -1) {
            perror(">>> [KONSUMENT]: read pipe error");
            exit(1);
        }

        sleep(rand() % 3);

        printf("\n>>> [KONSUMENT]: Czytam %d bajtów z pipe:\n", bytes);
        if (write(STDOUT_FILENO, buf, bytes) == -1) {
            perror(">>> [KONSUMENT]: error writing to stdout");
            exit(1);
        }
        if (write(outfile_fd, buf, bytes) == -1) {
            perror(">>> [KONSUMENT]: error writing to outfile");
            exit(1);
        }
    }

    if (close(pipe_fd) == -1) {
        perror(">>> [KONSUMENT]: close pipe error");
        exit(1);
    }
    if (close(outfile_fd) == -1) {
        perror(">>> [KONSUMENT]: close outfile error");
        exit(1);
    }

    return 0;
}
