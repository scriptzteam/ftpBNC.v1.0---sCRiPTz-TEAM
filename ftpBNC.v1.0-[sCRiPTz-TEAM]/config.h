#ifndef FTPBNC_CONFIG_H
#define FTPBNC_CONFIG_H

#include <stdbool.h>

typedef struct {
    char*   listenIP;
    int     listenPort;
    char*   remoteHost;
    int     remotePort;
    bool    idnt;
    int     identTimeout;
    int     idleTimeout;
    int     writeTimeout;
    bool    dnsLookup;
    char*   pidFile;
    char*   welcomeMsg;
} Config;

Config* Config_new();
Config* Config_loadBuffer(const char* buffer);
Config* Config_loadFile(const char* path);
Config* Config_loadEmbedded(const char* key);
char* Config_saveBuffer(Config* c);
void Config_free(Config** cp);

#endif
