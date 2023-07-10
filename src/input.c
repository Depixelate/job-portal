#define BUF_SIZE 4096
#include <stdio.h>

char *input(const char *msg) {
    static char buf[BUF_SIZE];
    printf("%s", msg);
    fgets(buf, BUF_SIZE, stdin);
    return buf;
}