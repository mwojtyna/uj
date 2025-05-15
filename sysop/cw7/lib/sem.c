#include "sem.h"
#include <fcntl.h>
#include <stdio.h>

sem_t* libsem_init(const char* name, int value) {
    sem_t* s = sem_open(name, O_CREAT | O_EXCL, 0644, value);
    if (s == SEM_FAILED) {
        perror("sem_open (init) error");
        return NULL;
    }
    return s;
}

sem_t* libsem_open(const char* name) {
    sem_t* s = sem_open(name, 0);
    if (s == SEM_FAILED) {
        perror("sem_open error");
        return NULL;
    }
    return s;
}

int libsem_get_value(sem_t* sem, int* value) {
    if (sem_getvalue(sem, value) == -1) {
        perror("sem_getvalue error");
        return 0;
    }
    return 1;
}

int libsem_close(sem_t* sem) {
    int my_sem = sem_close(sem);
    if (my_sem == -1) {
        perror("sem_close error");
        return 0;
    }
    return 1;
}

int libsem_delete(const char* name) {
    if (sem_unlink(name) == -1) {
        perror("sem_unlink error");
        return 0;
    }
    return 1;
}

int libsem_wait(sem_t* sem) {
    if (sem_wait(sem) == -1) {
        perror("sem_wait error");
        return 0;
    }
    return 1;
}

int libsem_post(sem_t* sem) {
    if (sem_post(sem) == -1) {
        perror("sem_post error");
        return 0;
    }
    return 1;
}
