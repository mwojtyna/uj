#ifndef LIBMQ_H
#define LIBMQ_H

#include <mqueue.h>

// Mateusz Wojtyna           29.04
// Biblioteka do obsługi semaforów

// Stwórz kolejkę
// Error: zwraca 0
mqd_t libmq_create(const char* name, int oflag, mode_t mode, struct mq_attr* attr);

// Otwórz kolejkę
// Error: zwraca 0
mqd_t libmq_open(const char* name, int oflag);

// Zamknij kolejkę
// Error: zwraca 0
int libmq_close(mqd_t fd);

// Usuń kolejkę
// Error: zwraca 0
int libmq_delete(const char* name);

// Zwróć atrybuty kolejki
// Error: zwraca 0
int libmq_getattr(mqd_t fd, struct mq_attr* attr);

// Ustaw atrybuty kolejki
// Error: zwraca 0
int libmq_setattr(mqd_t fd, struct mq_attr* newattr, struct mq_attr* oldattr);

// Wysyła wiadomość do kolejki
// Error: zwraca 0
int libmq_send(mqd_t fd, const char* msg_ptr, size_t msg_len, unsigned int msg_prio);

// Odbiera wiadomość z kolejki
// Error: zwraca 0
int libmq_receive(mqd_t fd, char* msg_ptr, size_t msg_len, unsigned int* msg_prio);

#endif
