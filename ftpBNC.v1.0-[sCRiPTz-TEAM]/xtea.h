#ifndef FTPBNC_XTEA_H
#define FTPBNC_XTEA_H

#include <stdio.h>

#define XTEA_BLOCK_SIZE     8
#define XTEA_KEY_SIZE       16

ssize_t XTeaEncryptECB(const unsigned char* src, size_t srcLen,
                       unsigned char* dst, size_t dstSize,
                       const unsigned char* key);
ssize_t XTeaDecryptECB(const unsigned char* src, size_t srcLen,
                       unsigned char* dst, size_t dstSize,
                       const unsigned char* key);

int XTeaGenerateIVec(unsigned char ivec[XTEA_BLOCK_SIZE]);
ssize_t XTeaEncryptCBC(const unsigned char* src, size_t srcLen,
                       unsigned char* dst, size_t dstSize,
                       const unsigned char ivec[XTEA_BLOCK_SIZE],
                       const unsigned char key[XTEA_KEY_SIZE]);
ssize_t XTeaDecryptCBC(const unsigned char* src, size_t srcLen,
                       unsigned char* dst, size_t dstSize,
                       const unsigned char ivec[XTEA_BLOCK_SIZE],
                       const unsigned char key[XTEA_KEY_SIZE]);

#endif
