/* A safe free funciton */
#include <stdio.h>
#include <stdlib.h>

void _safe_free(void **pp) {
    if (pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL; 
    }
}

#define safe_free(p) _safe_free((void**) &(p))

int main() 
{ 
    int *pi;
    pi = (int*) malloc(sizeof(int)); 
    *pi = 5;
    printf("Before: %p\n",pi); 
    safe_free(pi);
    printf("After: %p\n",pi); 
    safe_free(pi);
    return (EXIT_SUCCESS);
}
