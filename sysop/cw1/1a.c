#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    uid_t uid = getuid();
    gid_t gid = getgid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgrp();

    printf("Dane obecnego procesu:\n");
    printf("UID: %u\n", uid);
    printf("GID: %u\n", gid);
    printf("PID: %u\n", pid);
    printf("PPID: %u\n", ppid);
    printf("PGID: %u\n", pgid);

    return 0;
}
