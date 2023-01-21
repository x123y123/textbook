#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t string_len(char *string)
{
    size_t len = 0;
    while(*(string++)) {
        len++;
    }
    return len;
}

int main()
{
    char *ptr = (char*) malloc(strlen("Hello World!") + 1);
    strcpy(ptr, "Hello World!");
 
    printf("%zu\n", string_len(ptr));
    return 0;
}
