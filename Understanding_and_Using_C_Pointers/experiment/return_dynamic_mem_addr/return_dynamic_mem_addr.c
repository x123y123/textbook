#include <stdio.h>
#include <stdlib.h>

char *blanks(int number) 
{
    char *spaces = (char*) malloc(number + 1);
    for (int i = 0; i<number; i++) {
        spaces[i] = '#';
    }
    spaces[number] = '\0';
    return spaces;
}

int main(int argc, char **argv)
{
    char *tmp = blanks(atoi(argv[1]));
    //printf("[%s]\n", blanks(atoi(argv[1])));
    printf("[%s]\n", tmp);
    free(tmp);
    return 0;
}
