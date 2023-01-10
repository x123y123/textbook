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
### Using malloc()
```c
void *malloc(size_t);
```
The follow steps are performed when the `malloc()` is executed:
1. Memory is allocated from heap
2. The memory is **not** modified or otherwise cleared
3. The first byte's address is returned

#### Failing to allocate memory
If you declare a pointer but fail to allocate memory to the address it points to before using it, that memory will usually contain garbage, resulting typically in an invalid memory reference.
#### Using malloc with static and global pointers
We cannot use a function call when initializing a static or global variable.
```c
static int *pi = malloc((int)); // it will generate a compile-time error message
```
We cannot use a separate assignment statement with global variables because global variables are declared outside of a function and exe‐ cutable code, we can use:
```c
static int *pi;
pi = malloc(sizeof(int));
```

### Using calloc()
```c
void *calloc(size_t numElements, size_t elementSize);
// To clear memory means its contents are set to all binary zeros.
```
The following example where pi is allocated a total of 20 bytes, all containing zeros:
```c
int *pi = calloc(5, sizeof(int));   
// sizeof(int) = 4 bytes
// 5 * 4 bytes = 20 bytes
```
if using `malloc`:
```c
// memset() will fill a block with a value.
// first argument is a pointer to the buffer to fill.
// second argument is the value used to fill the buff.
// the last argument is the number of bytes to be set.

int *pi = malloc(5 * sizeof(int)); 
memset(pi, 0, 5* sizeof(int));
```
> the execution of `calloc()` may take longer than using `malloc()`

### Using realloc()
```c
void *realloc(void *ptr, size_t size);

// the first argument is a pointer to the original block
// the second argument is the requested size
// the return value is a pointer to the reallocated memory
```
* If the `size is less than` what is currently allocated, then the excess memory is `returned to the heap`. There is ***no guarantee*** that the excess memory will be cleared. 
* If the `size is greater than` what is currently allocated, then if possible, the memory will be allocated from the region immediately following the current allocation. Otherwise, memory is allocated from a different region of the heap and the old memory is `copied` to the new region.
* If the size is zero and the pointer is not null, then the pointer will be freed.
### Using free()
```c
void free(void *ptr);
```
* The pointer argument should contain the address of memory allocated by a malloc type function.
* This memory is returned to the heap.
#### Assigning NULL to a Freed pointer
An example of this approach follow:
```c
int *pi = (int *) malloc(sizeof(int));
// ...
free(pi);
pi = NULL;
```
* Pointers can cause problems even after they have been freed.
* As a result, some programmers will explicitly assign NULL to a pointer to designate the pointer as invalid. 
#### The Heap and System Memory
* The heap typically `uses operating system functions to manage` its memory.
* The heap manager does `not necessarily return memory to the operating system` when the **free()** is called.
#### Freeing Memory upon Program Termination
* With an abnormal program termination, cleanup may not be possible. Thus, there is no reason to free allocated memory before the application terminates.
* Thus, ensuring that all memory is free before program termination.

### Dangling Pointers
If a pointer still references the original memory after it has been freed, it is called a dangling pointer, somtimes call it `premature free`.
* Example:
```c
int *pi = (int *) malloc(sizeof(int));
*pi = 8;
free(pi);
*pi = 10;   // Dangling pointer
```
#### Dealing with Dangling Pointers
Several approaches exist for dealing with dangling pointers, including:
* Setting a pointer to NULL after freeing it. 
* Writing special functions to replace the free function.
* Some systems (runtime/debugger) will overwrite data when it is freed (e.g., 0xDEADBEEF - Visual Studio will use 0xCC, 0xCD, or 0xDD, depending on what is freed). 
* Use third-party tools to detect dangling pointers and other problems.
> * Displaying pointer values can be helpful in debugging dangling pointers, but you need to be careful how they are displayed.
> * The assert macro can also be useful, as demonstrated in “Dealing with Uninitialized Pointers” on page 162.
>> The `Mudflap` Libraries provide a similar capability for the GCC compiler. Its runtime library supports the detection of memory leaks, among other things. This detection is accomplished by instrumenting the pointer dereferencing operations.
#### Garbage Collection in C
When memory is no longer needed, it is collected and made avail‐ able for use later in the program. The deallocated memory is referred to as garbage. Hence, the term garbage collection denotes the processing of this memory.
#### Resource Acquisition Is Initialization
* It addresses the allocation and deallocation of resources in C++. The technique is useful for guaranteeing the allocation and subsequent deallocation of a resource in the presence of exceptions. 
* The GNU extension uses a macro called RAII_VARIABLE. It declares a variable and associates with the variable:
    * A type
    * A function to execute when the variable is created
    * A function to execute when the variable goes out of scope
The macro is shown below:
```c
#define RAII_VARIABLE(vartype,varname,initval,dtor) \
    void _dtor_ ## varname (vartype * v) { dtor(*v); } \
    vartype varname __attribute__((cleanup(_dtor_ ## varname))) = (initval)
```
#### Using Exception Handlers
Another approach to deal with the deallocation of memory is to use exception han‐ dling.
```c
_try        
_except
_finally    
_leave
// Example -------
_try {
    //guarded code
} _finally {
    // termination code
}
// ...

```
> exception handling is not a standard part of C.
