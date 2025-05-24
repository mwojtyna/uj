#include "common.h"
#include "libmq.h"
#include "utils.h"
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

mqd_t server_queue;

void cleanup(void) {
    libmq_close(server_queue);
    libmq_delete(SERVER_QUEUE_NAME);
}

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\n[SERVER] Cleaning up...\n");
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    CheckError(atexit(cleanup) == 0);
    CheckError(signal(SIGINT, signal_handler) != SIG_ERR);

    srand(time(NULL));

    struct mq_attr attr = {.mq_flags = 0, .mq_maxmsg = 10, .mq_msgsize = MSG_SIZE, .mq_curmsgs = 0};

    mqd_t server_queue = libmq_create(SERVER_QUEUE_NAME, O_CREAT | O_RDONLY, 0666, &attr);
    CheckError(server_queue);

    printf("[SERVER] Queue %s created\n", SERVER_QUEUE_NAME);
    printf("[SERVER] descriptor=%d maxmsg=%ld msgsize=%ld\n", server_queue, attr.mq_maxmsg,
           attr.mq_msgsize);

    char msg[MSG_SIZE];
    char expr[MSG_SIZE];
    char res_str[MSG_SIZE];
    char client_queue_name[CLIENT_QUEUE_NAME_LEN];
    while (1) {
        // Odbierz wiadomość
        CheckError(libmq_receive(server_queue, msg, sizeof msg, NULL));

        // Oblicz wynik
        pid_t pid;
        int res_len;
        if (sscanf(msg, "%d %[^\n]", &pid, expr) != 2) {
            printf("[SERVER] Error parsing client message: '%s'\n", msg);
            continue;
        } else {
            printf("[SERVER] Received message from PID %d: '%s'\n", pid, msg);

            double a, b, res;
            char op;

            if (sscanf(expr, "%lf %c %lf", &a, &op, &b) != 3 &&
                sscanf(expr, "%lf%c%lf", &a, &op, &b) != 3) {
                printf("[SERVER] Error: invalid expression format: '%s'\n", expr);
                continue;
            }

            switch (op) {
                case '+':
                    res = a + b;
                    break;
                case '-':
                    res = a - b;
                    break;
                case '*':
                    res = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        printf("[SERVER] Error: dividing by zero\n");
                        continue;
                    } else {
                        res = a / b;
                        break;
                    }

                default:
                    printf("[SERVER] Error: invalid operation '%c'\n", op);
                    continue;
            }
            res_len = snprintf(res_str, sizeof res_str, "%.6lf", res);
        }

        // Nazwa kolejki klienta
        int name_len = snprintf(client_queue_name, sizeof client_queue_name, "/%d", pid);
        CheckError(name_len > 0 && name_len <= sizeof client_queue_name);

        sleep(rand() % 2);

        mqd_t client_queue = libmq_open(client_queue_name, O_WRONLY);
        CheckError(client_queue);
        libmq_send(client_queue, res_str, res_len, 0);
        libmq_close(client_queue);

        printf("[SERVER] Sent '%s'\n", res_str);
    }

    return 0;
}
