#ifndef FTPBNC_IDENT_H
#define FTPBNC_IDENT_H

#include <arpa/inet.h>
#include <time.h>
#include <stdbool.h>
#include "misc.h"

#define IDENT_LEN 256

bool identLookup(const struct sockaddr_any* localAddr,
                 const struct sockaddr_any* peerAddr,
                 time_t timeout, char* user);

#endif
