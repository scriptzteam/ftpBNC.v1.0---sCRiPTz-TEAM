#ifndef FTPBNC_HEX_H
#define FTPBNC_HEX_H

#include <sys/types.h>

ssize_t hexEncode(const char* src, size_t srcLen, char* dst, size_t dstSize);
ssize_t hexDecode(const char* src, size_t srcLen, char* dst, size_t dstSize);

#endif
