#include "libmq.h"
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <sys/types.h>

mqd_t libmq_create(const char* name, int oflag, mode_t mode, struct mq_attr* attr) {
    mqd_t fd = mq_open(name, oflag, mode, attr);
    if (fd == -1) {
        perror("mq_open (create) error");
        return 0;
    }
    return fd;
}

mqd_t libmq_open(const char* name, int oflag) {
    mqd_t fd = mq_open(name, oflag);
    if (fd == -1) {
        perror("mq_open error");
        return 0;
    }
    return fd;
}

int libmq_close(mqd_t fd) {
    if (mq_close(fd) == -1) {
        perror("mq_close error");
        return 0;
    } else {
        return 1;
    }
}

int libmq_delete(const char* name) {
    if (mq_unlink(name) == -1) {
        perror("mq_unlink error");
        return 0;
    } else {
        return 1;
    }
}

int libmq_getattr(mqd_t fd, struct mq_attr* attr) {
    if (mq_getattr(fd, attr) == -1) {
        perror("mq_getattr error");
        return 0;
    } else {
        return 1;
    }
}

int libmq_setattr(mqd_t fd, struct mq_attr* newattr, struct mq_attr* oldattr) {
    if (mq_setattr(fd, newattr, oldattr) == -1) {
        perror("mq_setattr error");
        return 0;
    } else {
        return 1;
    }
}

int libmq_send(mqd_t fd, const char* msg_ptr, size_t msg_len, unsigned int msg_prio) {
    if (mq_send(fd, msg_ptr, msg_len, msg_prio) == -1) {
        perror("mq_send error");
        return 0;
    } else {
        return 1;
    }
}

int libmq_receive(mqd_t fd, char* msg_ptr, size_t msg_len, unsigned int* msg_prio) {
    if (mq_receive(fd, msg_ptr, msg_len, msg_prio) == -1) {
        perror("mq_receive error");
        return 0;
    } else {
        return 1;
    }
}
