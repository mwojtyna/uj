#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE_P 100

// Mateusz Wojtyna                                  Kraków, 10.04
// PRODUCENT
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr, "%s <potok> <plik_wejsciowy>\n", argv[0]);
        exit(1);
    }
    char* pipe_name = argv[1];
    char* infile_name = argv[2];

    srand(time(NULL));

    int pipe_fd = open(pipe_name, O_WRONLY);
    if (pipe_fd == -1) {
        perror(">>> [PRODUCENT]: open pipe error");
        exit(1);
    }

    int infile_fd = open(infile_name, O_RDONLY);
    if (infile_fd == -1) {
        perror(">>> [PRODUCENT]: open infile error");
        exit(1);
    }

    char buf[BUF_SIZE_P];
    int bytes;
    while ((bytes = read(infile_fd, buf, BUF_SIZE_P)) != 0) {
        if (bytes == -1) {
            perror(">>> [PRODUCENT]: read infile error");
            exit(1);
        }

        sleep(rand() % 2);

        printf("\n>>> [PRODUCENT]: Wpisuję %d bajtów do pipe:\n", bytes);
        if (write(STDOUT_FILENO, buf, bytes) == -1) {
            perror(">>> [PRODUCENT]: error writing to stdout");
            exit(1);
        }
        if (write(pipe_fd, buf, bytes) == -1) {
            perror(">>> [PRODUCENT]: error writing to pipe");
            exit(1);
        }
    }

    if (close(pipe_fd) == -1) {
        perror(">>> [PRODUCENT]: error closing pipe");
        exit(1);
    }
    if (close(infile_fd) == -1) {
        perror(">>> [PRODUCENT]: close infile error");
        exit(1);
    }

    return 0;
}
