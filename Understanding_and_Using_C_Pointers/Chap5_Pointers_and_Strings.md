# Chap 5: Pointers and Strings
Common string operations:
* comparing
* copying
* concatenating
## String Fundamentals
* terminate with **ASCII** `NUL(\0)` caracter.
* Arrays of char have been used to represent smaller integer units, such as boolean, to `conserve memory space` in an application.
> Two types of strings in C:
> * Byte string(char data): in `string.h`.
> * Wide string(wchar_t data): 16 or 32 bits, in `wchar.h`, useful in applications that support foreign languages.

#### NULL v.s. NUL
* NULL is used as a special `pointer`, `((void*)0)`.
* NUL is `cahr`.

### The String Literal Pool

> * gcc uses `-fwitable-strings` to turn off string pooling.
