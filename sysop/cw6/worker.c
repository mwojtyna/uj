#include "libsem.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Mateusz Wojtyna                   29.04
// Program do realizujący sekcje krytyczne
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Nie podano poprawnych argumentów!\n");
        fprintf(stderr, "%s <semaphor_name> <liczba_sekcji_krytycznych>\n", argv[0]);
        exit(1);
    }

    char* sem_name = argv[1];
    int critical_sections = atoi(argv[2]);

    // Żeby każdy proces miał inny seed (procesy uruchamiane są w tym samym czasie)
    srand(time(NULL) + getpid());

    sem_t* sem = libsem_open(sem_name);
    CheckError(sem != NULL);

    int sem_val;
    for (int i = 0; i < critical_sections; i++) {
        // Wypisuję wiadomość na końcu, żeby wiadomości nie były pomieszane
        char out[1024];
        int offset = 0;

        // ------- sekcja prywatna ------
        CheckError(libsem_get_value(sem, &sem_val));
        offset += sprintf(out + offset,
                          "\n[PID=%d, i=%d, sem=%d] sekcja prywatna przed sekcją krytyczną\n",
                          getpid(), i, sem_val);

        sleep(rand() % 3);

        // ------- sekcja krytyczna ------
        {
            CheckError(libsem_wait(sem));
            CheckError(libsem_get_value(sem, &sem_val));
            offset += sprintf(out + offset, "\t!!! [PID=%d, i=%d, sem=%d] SEKCJA KRYTYCZNA\n",
                              getpid(), i, sem_val);

            // Czytaj wartość z pliku
            int file_fd = open(FILE_NAME, O_RDONLY, 0644);
            CheckError(file_fd != -1);

            char read_buf[32];
            ssize_t read_bytes = read(file_fd, read_buf, sizeof(read_buf) - 1);
            CheckError(read_bytes != -1);
            read_buf[read_bytes] = '\0';
            CheckError(close(file_fd) != -1);

            int cur_num = atoi(read_buf);
            offset += sprintf(out + offset,
                              "\t!!! [PID=%d, i=%d, sem=%d] odczytano z %s: %d, zwiększamy do %d\n",
                              getpid(), i, sem_val, FILE_NAME, cur_num, cur_num + 1);

            sleep(rand() % 3);

            // Zapisz do pliku
            cur_num++;
            file_fd = open(FILE_NAME, O_WRONLY | O_TRUNC, 0644);
            CheckError(file_fd != -1);

            sprintf(read_buf, "%d\n", cur_num);
            CheckError(write(file_fd, read_buf, strlen(read_buf)) != -1);
            CheckError(close(file_fd) != -1);
        }

        // ------- koniec sekcji krytycznej ------
        CheckError(libsem_post(sem));
        CheckError(libsem_get_value(sem, &sem_val));
        offset += sprintf(out + offset, "[PID=%d, i=%d, sem=%d] po sekcji krytycznej\n", getpid(),
                          i, sem_val);

        printf("%s", out);
    }

    return 0;
}
