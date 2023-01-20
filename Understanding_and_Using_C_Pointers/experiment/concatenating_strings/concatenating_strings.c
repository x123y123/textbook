/* combine two error message strings */
// Tips: first, need to allocate enough memory for both strings, then copy the first strings to the buffer, and finally concatenate teh second string with the buffer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  char *strcpy(char *s1, const char *s2);
//  char *strcat(char *s1, const char *s2);

int main()
{
    char *error = "ERROR: ";
    char *error_message = "Not enough memory";

    char *buff = (char*) malloc(strlen(error) + strlen(error_message) + 1);
    strcpy(buff, error);
    strcat(buff, error_message);

    printf("%s\n", error);
    printf("%s\n", error_message);
    printf("%s\n", buff);

    free(buff);
    buff = NULL;

    return 0;
}

