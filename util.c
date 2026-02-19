#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>

// Converts 20-byte binary SHA-1 to a 40-character hex string
void bytesToHex(const unsigned char *bytes, char *hexOut) {
    for (int i = 0; i < 20; i++) {
        sprintf(hexOut + (i * 2), "%02x", bytes[i]);
    }
    hexOut[40] = '\0';
}

// Converts a 40-character hex string back to 20-byte binary
void hexToBytes(const char *hexIn, unsigned char *bytesOut) {
    for (int i = 0; i < 20; i++) {
        sscanf(hexIn + (i * 2), "%02x", (unsigned int *)&bytesOut[i]);
    }
}


int ensureDirExists(const char *path) {
    char temp[1024];
    char *p = NULL;
    size_t len;

    snprintf(temp, sizeof(temp), "%s", path);
    len = strlen(temp);
    if (temp[len - 1] == '/') temp[len - 1] = 0;

    for (p = temp + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            if (mkdir(temp, 0755) == -1 && errno != EEXIST) return -1;
            *p = '/';
        }
    }
    if (mkdir(temp, 0755) == -1 && errno != EEXIST) return -1;
    return 0;
}

void die(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}



// Returns the size of a file in bytes
long getFileSize(const char *fileName) {
    struct stat st;
    if (stat(fileName, &st) == 0)
        return st.st_size;
    return -1;
}
