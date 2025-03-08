#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    uid_t uid = getuid();
    gid_t gid = getgid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgrp();

    printf("Potomek: UID=%u, GID=%u, PID=%u, PPID=%u, PGID=%u\n", uid, gid, pid,
           ppid, pgid);

    return 0;
}
