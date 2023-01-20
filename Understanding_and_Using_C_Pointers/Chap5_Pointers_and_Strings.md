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
This area of memory holds the character sequences making up a string.
*  Initializing an array of char
```c
char header[] = "Media player"; // 12Bytes caracters + 1Byte NUL
```
* Initializing a pointer to a char
```c
char *header = (char*) malloc(strlen("Media Player")+1);
// char *header = (char*) malloc(13);
strcpy(header, "Media Player");
```
> when determining the length of a string to be used with the `malloc`:
> * Always remember to add one for the `NUL` terminator.
> * Don't use **sizeof**, `sizeof` operator will return the size of an array or pointer, not the length of string.
### Memory region to string
* `global` memory: will always be available and are accessible by multiple functions.
* `static` memory: will always be available but are accessible only to their defining function.
* allcate to `heap`: will persist until they are released and may be used in multiple functions. 
## Standard String Operations
### Comparing Strings
```c
int strcmp(const char *s1, const char *s2);

/*
    return value = 0: if strings are equal
    return value > 0: if the first non-matching character in s1 is greater (in ASCII) than that of s2 .
    return value < 0: if the first non-matching character in s1 is lower (in ASCII) than that of s2 .
*/
```
#### Using an array name or a string literal by themselves will return their addresses.
```c
char command[16];

scanf("%s", command);       // we tried to assign the string literal's address to command, it will cause syntax error
if(command = "Quit") {      // the equality operator compares the address
    //...
}
```
### Copying Strings
```c
char *strcpy(char *s1, const char *s2);
```
A common application is to read in a series of strings and store each of them in an array using a minimum amount of memory. This can be accomplished by creating an array sized to handle the largest string that the user might enter and then reading it into this array. On the basis of the string read in, we can then allocate just the right amount of memory. 

* Two pointers can reference the same string, when two pointers reference the same location is called `aliasing`.
```c
char *pageHeader[300];

pageHeader[12] = "Hello";
pageHeader[13] = pageHeader[12];
```

### Concatenating Strings(merge two strings)
```c
char *strcat(char *s1, const char *s2);
```
