#include "common.h"
#include "libmq.h"
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Mateusz Wojtyna      24.05.2025
// Klient

mqd_t client_queue;
mqd_t server_queue;
char client_queue_name[CLIENT_QUEUE_NAME_LEN];

void cleanup(void) {
    if (client_queue >= 0) {
        libmq_close(client_queue);
        libmq_delete(client_queue_name);
    }
}

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\n[CLIENT] Cleaning up...\n");
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    CheckError(atexit(cleanup) == 0);
    CheckError(signal(SIGINT, signal_handler) != SIG_ERR);

    srand(time(NULL));

    pid_t pid = getpid();
    int n = snprintf(client_queue_name, sizeof client_queue_name, "/%d", pid);
    CheckError(n > 0 && n <= sizeof client_queue_name);

    struct mq_attr attr = {
        .mq_flags = 0, .mq_maxmsg = MSG_NUM, .mq_msgsize = MSG_SIZE, .mq_curmsgs = 0};

    mqd_t client_queue = libmq_create(client_queue_name, O_CREAT | O_RDONLY, 0666, &attr);
    CheckError(client_queue);

    printf("[CLIENT] Queue %s created\n", client_queue_name);
    printf("[CLIENT] descriptor=%d maxmsg=%ld msgsize=%ld\n", server_queue, attr.mq_maxmsg,
           attr.mq_msgsize);

    mqd_t server_queue = libmq_open(SERVER_QUEUE_NAME, O_WRONLY);
    CheckError(server_queue);

    printf("[CLIENT] Enter expression or Ctrl+D to close: ");

    while (1) {
        char expr[MSG_SIZE];
        char msg[MSG_SIZE];
        char res[MSG_SIZE];

        if (!fgets(expr, sizeof expr, stdin)) {
            if (feof(stdin)) {
                printf("\n[CLIENT] EOF, closing...");
                break;
            }
            perror("[CLIENT] fgets error");
            continue;
        }

        expr[strcspn(expr, "\n")] = '\0'; // Zakończ wyrażenie matematyczne

        // Wyślij wiadomość
        int msg_len = snprintf(msg, sizeof msg, "%d %s", (int)pid, expr);
        CheckError(n > 0 && n <= sizeof msg);
        CheckError(libmq_send(server_queue, msg, msg_len, 0));

        sleep(rand() % 2);

        // Odbierz wiadomość
        memset(res, 0, sizeof res);
        CheckError(libmq_receive(client_queue, res, sizeof res, NULL));
        res[sizeof res - 1] = '\0';

        if (strncmp(res, "ERROR:", 6) == 0) {
            char* reason = res + 7; // pomiń "ERROR: "
            printf("[CLIENT] Error: %s\n", reason);
        } else {
            printf("[CLIENT] Result: %s\n", res);
        }
        printf("[CLIENT] Enter expression or Ctrl+D to close: ");
    }

    return 0;
}
