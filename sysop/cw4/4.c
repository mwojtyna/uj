#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE_P 100
#define BUF_SIZE_K 80

// Mateusz Wojtyna                                                            Kraków, 04.04
// Przy pomocy potokow nienazwanych systemu UNIX zaimplementowac problem "Pro-
// ducenta i konsumenta". Dla zademonstrowania, ze nie doszlo do utraty ani zwielokrot-
// nienia towaru, niech Producent pobiera "surowiec" (np. porcje bajtow) z pliku tekstowego
// i wstawia go jako towar do potoku, a Konsument niech umieszcza pobrany z potoku
// towar w innym pliku tekstowym (porcje danych Producenta i Konsumenta nie musza byc
// rowne). Po zakonczeniu dzialania programow (wyczerpaniu zasobow "surowca") oba pliki
// tekstowe powinny byc identyczne (mozna to sprawdzic poleceniem diff -s, ktore najlepiej
// umiescic w pliku Makefile po poleceniu uruchomienia programu). Oba procesy niech
// drukuja odpowiednie komunikaty na ekranie, w tym towar, ktory przesylaja. Do zasymu-
// lowania roznych szybkosci dzialania programow uzyc funkcji sleep, np. z losowym czasem
// usypiania. Do czytania/pisania danych z/do pliku tekstowego, jak rowniez wypisywania
// ich na ekran uzyc funkcji read i write.
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Nie podano nazwy plików!\n");
        fprintf(stderr, "%s <plik_wejsciowy> <plik_wyjsciowy>\n", argv[0]);
        exit(1);
    }
    char* infile_name = argv[1];
    char* outfile_name = argv[2];

    srand(time(NULL));

    int pipe_fds[2]; // 0: read, 1: write
    if (pipe(pipe_fds) == -1) {
        perror("pipe() error");
        _exit(1);
    }
    switch (fork()) {
        case -1:
            perror("fork() error");
            _exit(1);

        case 0: {
            // Potomek (konsument)
            if (close(pipe_fds[1])) {
                perror("error closing write end of pipe");
                _exit(1);
            }

            int outfile_fd = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (outfile_fd == -1) {
                perror("open outfile error");
                _exit(1);
            }

            char buf[BUF_SIZE_K]; 
            int bytes;
            while ((bytes = read(pipe_fds[0], buf, BUF_SIZE_K)) != 0) {
                if (bytes == -1) {
                    perror("read pipe error");
                    _exit(1);
                }

                sleep(rand() % 3);

                printf("\n>>> [KONSUMENT]: Czytam %d bajtów z pipe:\n", bytes);
                if (write(STDOUT_FILENO, buf, bytes) == -1) {
                    perror("error writing to stdout");
                    _exit(1);
                }
                if (write(outfile_fd, buf, bytes) == -1) {
                    perror("error writing to outfile");
                    _exit(1);
                }
            }

            if (close(pipe_fds[0]) == -1) {
                perror("close read end of pipe error");
                _exit(1);
            }
            if (close(outfile_fd) == -1) {
                perror("close outfile error");
                _exit(1);
            }
            exit(0);
        }

        default: {
            // Macierzysty (producent)
            if (close(pipe_fds[0])) {
                perror("error closing read end of pipe");
                _exit(1);
            }

            int infile_fd = open(infile_name, O_RDONLY);
            if (infile_fd == -1) {
                perror("open infile error");
                exit(1);
            }

            char buf[BUF_SIZE_P]; 
            int bytes;
            while ((bytes = read(infile_fd, buf, BUF_SIZE_P)) != 0) {
                if (bytes == -1) {
                    perror("read infile error");
                    _exit(1);
                }

                sleep(rand() % 2);

                printf("\n>>> [PRODUCENT]: Wpisuję %d bajtów do pipe:\n", bytes);
                if (write(STDOUT_FILENO, buf, bytes) == -1) {
                    perror("error writing to stdout");
                    _exit(1);
                }
                if (write(pipe_fds[1], buf, bytes) == -1) {
                    perror("error writing to pipe");
                    _exit(1);
                }
            }

            if (close(pipe_fds[1]) == -1) {
                perror("error closing write end of pipe");
                exit(1);
            }
            if (close(infile_fd) == -1) {
                perror("close infile error");
                exit(1);
            }
            if (wait(NULL) == -1) {
                perror("wait() error");
                exit(1);
            }
            printf("\n");

            return 0;
        }
    }
}
