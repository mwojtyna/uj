// Mateusz Wojtyna 30.05
// Program realizuje problem wzajemnego wykluczania wątków przy użyciu mutexów.
// Przyjmuje jao argumenty liczbę wątków oraz liczbe ich sekcji krytycznych.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_SLEEP 3

// 1-indexed
void gotoXY(int y, int x) {
    printf("\x1b[%d;%dH", y, x);
}

void clear_line() {
    printf("\x1b[2K");
}

int g_thread_log_start = 3;
int g_crit_section_count = 0;
int g_thread_count = 0;
int g_counter = 0;
pthread_mutex_t thread_mutex;

void* thread_fun(void* arg) {
    int thread_num = *((int*)arg);
    int print_line = g_thread_log_start + thread_num;

    sleep(rand() % MAX_SLEEP);

    for (int i = 0; i < g_crit_section_count; i++) {
        gotoXY(print_line, 0);
        clear_line();
        printf("Thread %d at iteration %d\n", thread_num, i);

        sleep(rand() % MAX_SLEEP);

        int mutex_lock_ret = 0;
        {
            if ((mutex_lock_ret = pthread_mutex_lock(&thread_mutex) != 0)) {
                fprintf(stderr, "Mutex lock error %s\n", strerror(mutex_lock_ret));
                int ret = 1;
                pthread_exit(&ret);
            }

            gotoXY(print_line, 40);
            printf("Thread %d at crit section at iteration %d with counter at %d\n", thread_num, i,
                   g_counter);

            int local_counter = g_counter;
            local_counter++;

            sleep(rand() % MAX_SLEEP);

            g_counter = local_counter;

            int mutex_unlock_ret = 0;
            if ((mutex_unlock_ret = pthread_mutex_unlock(&thread_mutex) != 0)) {
                fprintf(stderr, "Mutex unlock error %s\n", strerror(mutex_lock_ret));
                int ret = 1;
                pthread_exit(&ret);
            }
        }
    }

    gotoXY(print_line, 0);
    clear_line();
    printf("Thread %d finished\n", thread_num);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (system("clear") == -1) {
        perror("system() error");
        exit(1);
    }

    if (argc != 3) {
        fprintf(stderr, "Invalid arguments!\n");
        fprintf(stderr, "%s <thread_num> <crit_sections_num>\n", argv[0]);
        exit(1);
    }

    srand(time(NULL));

    g_thread_count = atoi(argv[1]);
    g_crit_section_count = atoi(argv[2]);
    g_thread_log_start += g_thread_count;

    int mutex_init_ret = 0;
    if ((mutex_init_ret = pthread_mutex_init(&thread_mutex, NULL) != 0)) {
        fprintf(stderr, "Mutex creation error %s\n", strerror(mutex_init_ret));
        exit(1);
    }
    printf("Thread mutex created at %p\n", (void*)&thread_mutex);

    pthread_t thread_handles[g_thread_count];
    int thread_args[g_thread_count];

    // Create threads
    for (int i = 0; i < g_thread_count; i++) {
        thread_args[i] = i;
        int ret = 0;
        if ((ret = pthread_create(&thread_handles[i], NULL, &thread_fun, &thread_args[i]) != 0)) {
            fprintf(stderr, "Mutex create error %s\n", strerror(ret));
            exit(1);
        }
        printf("Created thread %d with id %lu\n", i, thread_handles[i]);
    }

    // Join all threads
    for (int i = 0; i < g_thread_count; i++) {
        int thread_join_ret = 0;
        if ((thread_join_ret = pthread_join(thread_handles[i], NULL) != 0)) {
            fprintf(stderr, "Thread join error %s\n", strerror(thread_join_ret));
        }
    }

    gotoXY(g_thread_log_start + g_thread_count + 1, 0);
    printf("Global counter %d expected %d\n", g_counter, g_thread_count * g_crit_section_count);

    int mutex_destroy_ret = 0;
    if ((mutex_destroy_ret = pthread_mutex_destroy(&thread_mutex) != 0)) {
        fprintf(stderr, "Mutex destroy error %s\n", strerror(mutex_destroy_ret));
        exit(1);
    }

    return 0;
}
