#include <stdio.h>

int main()
{
#ifdef __STDC_VERSION__
    printf("__STDC_VERSION__ = %ld \n", __STDC_VERSION__);
#endif
#ifdef __STRICT_ANSI
    puts("__STRICT_ANSI");
#endif 
    return 0;
}
