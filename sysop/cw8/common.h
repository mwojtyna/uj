#ifndef COMMON_H
#define COMMON_H

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

#define CLIENT_QUEUE_NAME_LEN 32
#define SERVER_QUEUE_NAME "/server_queue"
#define MSG_SIZE 256
#define MSG_NUM 10

#endif
