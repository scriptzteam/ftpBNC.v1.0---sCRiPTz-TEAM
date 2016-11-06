#ifndef FTPBNC_CLIENT_H
#define FTPBNC_CLIENT_H

#include <arpa/inet.h>
#include <pthread.h>
#include "config.h"
#include "server.h"
#include "misc.h"

#define CLIENT_STACKSIZE 65536

typedef struct {
    pthread_t           threadId;
    int                 cSock;
    struct sockaddr_any cAddr;
    int                 rSock;
    struct sockaddr_any rAddr;
    Config*             cfg;
    Server*             srv;
} Client;

void Client_launch(Server* srv, int sock, const struct sockaddr_any* addr);

#endif
