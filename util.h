#ifndef UTIL_H
#define UTIL_H

void bytesToHex(const unsigned char* bytes, char* hexOut);
void hexToBytes(const char* hexIn, unsigned char* bytesOut);
int ensureDirExists(const char* path);
void die(const char* fmt, ...);
long getFileSize(const char* fileName);


#endif
