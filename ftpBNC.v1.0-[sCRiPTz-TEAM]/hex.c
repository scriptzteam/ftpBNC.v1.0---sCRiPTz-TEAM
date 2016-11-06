#include <ctype.h>
#include "hex.h"

ssize_t hexEncode(const char* src, size_t srcLen, char* dst, size_t dstSize)
{
    static const char lookup[] = {  '0', '1', '2', '3', '4',
                                    '5', '6', '7', '8', '9',
                                    'A', 'B', 'C', 'D', 'E', 
                                    'F' };

    char* dp = dst;
    const char* sp;
    ssize_t dstLen = 0;
    for (sp = src; srcLen > 0 && dstLen + 2 < (ssize_t)dstSize; sp++) {

        unsigned int ascii = (unsigned int) *sp;
        unsigned int digit2 = ascii % 16;
        ascii /= 16;
        unsigned int digit1 = ascii % 16;

        *dp++ = lookup[digit1];
        *dp++ = lookup[digit2];
        dstLen += 2;
        srcLen--;
    }

    if (srcLen > 0) { return -1; }

    *dp = '\0';
    return dstLen;
}

inline int hexDecodeChar(unsigned int ch)
{
    int digit;
    if (isdigit(ch)) {
        digit = ch - '0';
    }
    else {
        if (ch >= 'A' || ch <= 'F') {
            digit = ch - 'A' + 10;
        }
        else if (ch >= 'a' || ch <= 'f') {
            digit = ch - 'a' + 10;
        }
        else {
            return -1;
        }
    }
    return digit;
}

ssize_t hexDecode(const char* src, size_t srcLen, char* dst, size_t dstSize)
{
    if (srcLen % 2 != 0) { return -1; }

    char* dp = dst;
    const char* sp;
    ssize_t dstLen = 0;
    for (sp = src; srcLen > 0 && dstLen + 1 < (ssize_t)dstSize; sp += 2) {

        int digit1 = hexDecodeChar((unsigned int) *sp);
        if (digit1 == -1) { return -1; }

        int digit2 = hexDecodeChar((unsigned int) *(sp + 1));
        if (digit2 == -1) { return -1; }

        *dp++ = digit1 * 16 + digit2;
        dstLen++;
        srcLen -= 2;
    }

    if (srcLen > 0) { return -1; }

    *dp = '\0';
    return dstLen;
}
