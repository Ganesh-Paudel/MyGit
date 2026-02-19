#ifndef OBJECTSTORE_H
#define OBJECTSTORE_H

int cmdHashObject(const char* fileName);
void hashToHex();
int compressObject(const char* path, unsigned char* data, int len);
#endif
