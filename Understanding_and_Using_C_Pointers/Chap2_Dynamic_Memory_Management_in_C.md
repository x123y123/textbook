# Chap 2: Dynamic Memory Management in C
* when memory is allocated for `automatic variables`. In this case, variables are allocated to the enclosing function’s stack frame. In the case of static and global variables, memory is placed in the application’s data segment, where it is zeroed out.
* Instead of having to allocate memory to accommodate the largest possible size for a data structure, `only the actual amount required needs to be allocated`.

> Dynamic memory management = memory allocate + memory deallocate

## Dynamic Memory Allocation
Basic steps used for memory allocation in C:
1. malloc()
2. use this memory to support the application
3. free()

```c
int *pi = (int*) malloc(sizeof(int)); 
*pi = 5;
printf("*pi: %d\n", *pi);
free(pi);
```
#### malloc()
* if successful, it returns a pointer to memory allocated from the `heap`.
* if fails, it return s a `NULL` pointer.
Example:
```c
int *pi;

// *pi = (int *) malloc(sizeof(int));     // wrong
// *pi will assign the address returned by malloc to the address stored in pi, if this is the first time an assignment is made to the pointer, then the address contained in the pointer is probably invalid
pi = (int *) malloc(sizeof(int));         // correct
```
> Each time the malloc function (or similar function) is called, a corre‐ sponding call to the free function must be made when the application is done with the memory to avoid `memory leaks`.

```c
char *pc = (char *) malloc(sizeof(6));      // 5 bytes for characters + 1 byte for NUL(\0) termination character
```
### Memory Leaks
A memory leak occurs when allocated memory is never used again but is not freed. This can happen when:
* The memory’s address is lost
* The free function is never invoked though it should be (sometimes called a `hidden leak`)
> A problem with memory leaks is that the memory cannot be reclaimed and used later. The amount of memory available to the heap manager is decreased. If memory is repeatedly allocated and then lost, then the program may terminate when more memory is needed but malloc cannot allocate it because it ran out of memory. In extreme cases, the operating system may crash.
#### Hidden memory leaks
Memory leaks can also occur when freeing structures created using the struct keyword. If the structure contains pointers to dynamically allocated memory, then these pointers may need to be freed before the structure is freed.

## Dynamic Memory Allocation Functions
In `stdlib.h` header file:
* malloc  : Allocates memory from the heap
* realloc : Reallocates memory to a larger or smaller amount based on a previously allocated block of memory
* calloc  : Allocates and zeros out memory from the heap
* free    : Returns a block of memory to the heap
