#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <unistd.h>
#include "misc.h"
#include "server.h"
#include "client.h"

Server* Server_new()
{
    Server* s = calloc(1, sizeof(Server));
    if (!s) { return NULL; }

    s->sock = -1;

    return s;
}

void Server_free(Server** sp)
{
    if (*sp) {
        Server* s = *sp;
        if (s->sock >= 0) { close(s->sock); }
        free(s);
        *sp = NULL;
    }
}

bool Server_listen2(Server* s, const char* ip, int port)
{
    if (!ipPortToSockaddr(ip, port, &s->addr)) {
        fprintf(stderr, "Invalid listenip.\n");
        return false;
    }

    s->sock = socket(s->addr.san_family, SOCK_STREAM, 0);
    if (s->sock < 0) {
        perror("socket");
        return false;
    }

    {
        int optval = 1;
        setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    }

    if (bind(s->sock, &s->addr.sa, sockaddrLen(&s->addr)) < 0) {
        perror("bind");
        return false;
    }

    if (listen(s->sock, SOMAXCONN) < 0) {
        perror("listen");
        return false;
    }

    return true;
}

Server* Server_listen(Config* cfg)
{
    Server* s = Server_new();
    if (!s) {
        perror("Server_new");
        return NULL;
    }

    s->cfg = cfg;
    if (!Server_listen2(s, cfg->listenIP, cfg->listenPort)) {
        Server_free(&s);
        return NULL;
    }

    return s;
}

void Server_accept(Server* s)
{
    struct sockaddr_any addr;
    socklen_t len = sizeof(addr);
    int sock = accept(s->sock, &addr.sa, &len);
    if (sock < 0) {
        perror("accept");
        return;
    }

    Client_launch(s, sock, &addr);
}

void Server_loop(Server* s)
{
    while (true) {
      Server_accept(s);
    }
}
