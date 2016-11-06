#ifndef FTPBNC_SERVER_H
#define FTPBNC_SERVER_H

#include <sys/socket.h>
#include "config.h"
#include "misc.h"

typedef struct {
    int                 sock;
    struct sockaddr_any addr;
    Config*             cfg;
} Server;

Server* Server_listen(Config* cfg);
void Server_free(Server** sp);
void Server_loop(Server* s);

#endif
