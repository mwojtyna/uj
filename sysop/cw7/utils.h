#include <stdlib.h>

/*
=======================================================
Makro CheckError: wskaz lokalizacje bledu, wypisz nazwe
przekazywanego argumentu (#Arg) i zakoncz program.
=======================================================
*/
#define CheckError(Arg)                                                                            \
    if (!(Arg)) {                                                                                  \
        fprintf(stderr, "[ERROR] %s:%d (%s) -> CheckError argument: %s\n", __FILE__, __LINE__,     \
                __func__, #Arg);                                                                   \
        exit(EXIT_FAILURE);                                                                        \
    }
