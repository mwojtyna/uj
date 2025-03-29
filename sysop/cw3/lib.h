#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sig;
    int op;
} Args;

Args handleArgs(int argc, char* argv[]);
