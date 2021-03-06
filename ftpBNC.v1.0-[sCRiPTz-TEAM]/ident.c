#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include "ident.h"
#include "misc.h"

#define IDENT_PORT      113

bool identLookup(const struct sockaddr_any* localAddr,
                 const struct sockaddr_any* peerAddr,
                 time_t timeout, char* user)
{
    struct sockaddr_any addr;
    memcpy(&addr, peerAddr, sizeof(addr));
    switch (addr.san_family) {
        case AF_INET :
            addr.s4.sin_port = htons(IDENT_PORT);
            break;
        case AF_INET6 :
            addr.s6.sin6_port = htons(IDENT_PORT);
            break;
        default :
            return false;
    }

    int sock = socket(addr.san_family, SOCK_STREAM, 0);
    if (sock < 0) { return false; }

    setReadTimeout(sock, timeout);
    setWriteTimeout(sock, timeout);

    if (connect(sock, &addr.sa, sockaddrLen(&addr)) < 0) {
      close(sock);
      return false;
    }

    FILE* fp = fdopen(sock, "r+");
    if (!fp) {
        close(sock);
        return false;
    }

    int localPort = portFromSockaddr(localAddr);
    int remotePort = portFromSockaddr(peerAddr);

    if (fprintf(fp, "%i, %i\r\n", remotePort, localPort) < 0) {
        fclose(fp);
        return false;
    }

    int replyLocalPort;
    int replyRemotePort;

    int ret = fscanf(fp, "%i , %i : USERID :%*[^:]:%255s\r\n", &replyRemotePort,
                     &replyLocalPort, user);
    fclose(fp);

    return ret == 3 && replyLocalPort == localPort && replyRemotePort == remotePort;
}
