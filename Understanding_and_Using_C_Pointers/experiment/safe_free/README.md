# Safe free function
## Use gcc compile and execute
```shell
$ gcc safe_free.c
$ ./a.out
```
## Output
```shell
Before: 0x600000a04040
After: 0x0
```
## Experiment Record
#### Functions name issue (Error:)
If we use the function name "safefree()", it will cause error(implicit declaration in `C99`):
```shell
safe_free.c:21:5: error: implicit declaration of function 'safeFree' is invalid in C99 [-Werror,-Wimplicit-function-declaration]
    safeFree(pi);
        ^
```
So we need to change the function to `_safe_function()`.
#### Casting issue (Warning:)
```shell
safe_free.c:52:15: warning: incompatible pointer types passing 'int *' to parameter of type 'void **' [-Wincompatible-pointer-types]
    safe_Free(pi);
              ^~
```
So we need to let the pointer type to `void`:
```c
#define safe_free(p) _safe_free((void**) &p)
```
