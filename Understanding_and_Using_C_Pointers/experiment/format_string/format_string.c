#include <stdio.h>

//  int snprintf ( char * str, size_t size, const char * format, ... );

char *format(char *buffer, size_t size, const char *name, size_t quantity, size_t weight) 
{
    snprintf(buffer, size, "Item: %s Quantity: %zu Weight: %zu", name, quantity, weight);
    return buffer;
}

int main()
{
    char buffer[300];
    printf("%s\n", format(buffer, sizeof(buffer), "Axle", 25, 45));
    return 0;
}
