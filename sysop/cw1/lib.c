#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void printProcessData(char* name) {
    uid_t uid = getuid();
    gid_t gid = getgid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgrp();

    printf("%s: UID=%u, GID=%u, PID=%u, PPID=%u, PGID=%u\n", name, uid, gid, pid, ppid, pgid);
}
