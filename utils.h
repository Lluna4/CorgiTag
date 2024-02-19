#include <stdlib.h>
#include <string.h>

short read_short(char *nbt)
{
   unsigned short len = 0;
   
   len = (nbt[0] << 8) | nbt[1];
   return len;
}

char *read_string(char *nbt, short size)
{
    short len = size;
    char *ret;

    ret = (char *)calloc(len + 1, sizeof(char));
    strncpy(ret, nbt, len);
}