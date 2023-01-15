# What is the default C standard version(-std) for the current GCC?
A quick history of the standard:

* C89 was the first official C standard, published by ANSI in 1989.
* C90 was the ISO version of the standard, describing exactly the same language as C89. ANSI officially adopted ISO's version of the standard. There were two Technical Corrigenda, correcting some errors.
* C95 was an amendment to C90, adding a few features, mainly digraphs and wide character support. As far as I know, a merged version was never published.
* C99 was issued by ISO in 1999. There were three Technical Corrigenda.
* C11 was issued by ISO in 2011. There has been one Technical Corrigendum, fixing the definitions of __STDC_VERSION__ and __STDC_LIB_EXT1__.
## Minimal test program
* `c.c`
```c
#include <stdio.h>

int main(void) {
#ifdef __STDC_VERSION__
        printf("__STDC_VERSION__ = %ld \n", __STDC_VERSION__);
#endif
#ifdef __STRICT_ANSI__
            puts("__STRICT_ANSI__");
#endif
                return 0;
}

```

* Test with `test.sh`:
```c
#!/usr/bin/env bash
for std in c89 c99 c11 c17 gnu89 gnu99 gnu11 gnu17; do
    echo $std
    gcc -std=$std -o c.out c.c
    ./c.out
    echo
done
echo default
gcc -o c.out c.c
./c.out
```
* Output
```shell
c89
__STRICT_ANSI__

c99
__STDC_VERSION__ = 199901
__STRICT_ANSI__

c11
__STDC_VERSION__ = 201112
__STRICT_ANSI__

c17
__STDC_VERSION__ = 201710
__STRICT_ANSI__

gnu89

gnu99
__STDC_VERSION__ = 199901

gnu11
__STDC_VERSION__ = 201112

gnu17
__STDC_VERSION__ = 201710

default
__STDC_VERSION__ = 201710
```
## Summary
`gnu17` is used by default:

* `__STRICT_ANSI__`: GCC extension that is defined for -std=c but not for -std=gnu
* `__STDC_VERSION__`: C99+ ANSI C macro that set for each version. Not present in C89 where it was not yet defined by the standard.

## Reference
* [gcc.gnu.org](https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html)
* [stackoverflow](https://stackoverflow.com/questions/14737104/what-is-the-default-c-std-standard-version-for-the-current-gcc-especially-on-u)
