#include "shm.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int libshm_open(const char* name, int flags, mode_t mode) {
    int fd = shm_open(name, flags, mode);
    if (fd == -1) {
        perror("shm_open error");
        return -1;
    } else {
        return fd;
    }
}

int libshm_set_size(int fd, off_t length) {
    if (ftruncate(fd, length) == -1) {
        perror("ftruncate error");
        return 0;
    } else {
        return 1;
    }
}

void* libshm_map(int fd, size_t size) {
    void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap error");
        return NULL;
    } else {
        return addr;
    }
}

int libshm_unmap(void* addr, size_t size) {
    if (munmap(addr, size) == -1) {
        perror("munmap error");
        return 0;
    } else {
        return 1;
    }
}

int libshm_close(int fd) {
    if (close(fd) == -1) {
        perror("close error");
        return 0;
    } else {
        return 1;
    }
}

int libshm_delete(const char* name) {
    if (shm_unlink(name) == -1) {
        perror("shm_unlink error");
        return 0;
    } else {
        return 1;
    }
}
