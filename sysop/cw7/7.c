#include "buffer.h"
#include "lib/libsem.h"
#include "lib/libshm.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void cleanup() {
    CheckError(libsem_unlink(SEM_WRITE));
    CheckError(libsem_unlink(SEM_READ));
    CheckError(libshm_delete(SHM_NAME));
}

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\nCleaning up...\n");
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    CheckError(atexit(cleanup));

    return 0;
}
