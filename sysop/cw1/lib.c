#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void printProcessData() {
    uid_t uid = getuid();
    gid_t gid = getgid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgrp();

    printf("UID: %u\n", uid);
    printf("GID: %u\n", gid);
    printf("PID: %u\n", pid);
    printf("PPID: %u\n", ppid);
    printf("PGID: %u\n", pgid);
}
