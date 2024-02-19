#include <fcntl.h>
#include <unistd.h>
#include "CorgiTag.h"
int main(int argc, char *argv[])
{
    char *path;
    char *buffer = calloc(1025, sizeof(char));
    path = "pkt.pkt";
    int fd = open(path, O_RDONLY);
    read(fd, buffer, 1024);
    parse(buffer);
    int a = 0;
}