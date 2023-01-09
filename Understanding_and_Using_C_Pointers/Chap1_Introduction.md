# Chap 1: Introduction

## Pointers and Memory
* Static/Global: The lifetime of the application.
  * the scope of global: The entire file.
  * the scope of static: The function it is declared within.
* Automatic: While the function is excuting
  * the scope of automatic: The function it is declared within.
* Dynamic: Until the memory is freed.
  * Determined by the pointers that reference this memory.

## Declaring Pointers
```c
// All folowings are the same

int* pi;
int *pi;
int * pi;
int*pi;
```
There are severall points to remember:
* The content of pi should eventually be assigned the address of an integer variable.
* These variables have not been initialized and thus contain `garbage`.
* There is nothing inherent to a pointer’s implementation that suggests what type of data it is referencing or whether its contents are valid.
* However, the pointer type has been specified and the compiler will frequently complain when the pointer is not used correctly.
> By garbage, we mean the memory allocation could contain any value. When memory is allocated it is not cleared. The previous contents could be anything. If the previous contents held a floating point number, in‐ terpreting it as an integer would likely not be useful. Even if it contained an integer, it would not likely be the right integer. Thus, its contents are said to hold garbage.

## How to read a declaration - "Read them backward"
```c
const int *pci;
```
1. pci is a variable                                               `pci;`
2. pci is a pointer variable                                      `*pci;`
3. pci is a pointer variable to an integer                    `int *pci;`
4. pci is a pointer variable to a constant integer      `const int *pci;`

## Address of operator - "&"
> Assignment of integers to a pointer will generally cause a warning or error.

But if we cast an integer to a pointer to an integer:
```c
pi = (int *)num;
```
This will not generate a syntax error. When executed, though, the program may `terminate abnormally` when the program attempts to dereference the value `at address zero`.

## Displaying pointer values

```c
%x  // hexadecimal number 
%o  // octal number
%p  // Displays the value in an implementation-specific manner; typically as a hexadecimal number.
```
We usually use `%p` specifier for address.
## Virtual memory and pointers
* A virtual op‐ erating system allows a program to be split across the machine’s physical address space.
* An application is split into `pages/frames`. These pages represent areas of main memory.
* The pages of the application are allocated to different, potentially noncontiguous areas of memory and may not all be in memory at the same time.
* The address used by a program is a virtual address, this means `code and data in a page may be in different physical locations` as the program executes. 
* The virtual addresses are transparently mapped to real addresses by the operating system.

## Dereferencing a pointer using the "Indirection operator"
The indirection operator, `*`,also can call it `value of`.
Example:
```c
int num = 5;
int *pi = &num;
printf("%p\n", *pi);  // Display 5
```
## Pointer to Functions
```c
void (*foo)();  //The function is passed void and returns void.
```
## The concept of "NULL"
We often deal with several similar, yet distinct concepts, including:
* The null concept
* The null pointer constant 
* The NULL macro
* The ASCII NUL
* A null string
* The null statement
> When NULL is assigned to a pointer, it means the pointer does not point to anything.

The NULL macro is a constant integer zero cast to a pointer to void. In many libraries, it is defined as follows:
```c
#define NULL    ((void *)0)

// this define can be found in stddef.h, stdlib.h, stdio.h
```
The use of NULL and 0 are language-level symbols that represent a null pointer.

> A null pointer and an uninitialized pointer are different. An uninitial‐ ized pointer can contain any value, whereas a pointer containing NULL does not reference any location in memory.
```c
// pi is a pointer variable
pi = 0;
pi = NULL;
pi = 100;   // Syntax error
pi = num;   // Syntax error
//Interestingly, we can assign a zero to a pointer, but we cannot assign any other integer value. 
```
> A null pointer should never be dereferenced because it does not contain a valid address. When executed it will result in the program terminating.


### Using 0 or NULL
The meaning of zero changes depending on its context. It might mean the integer zero in some contexts, and it might mean a null pointer in a different context. Consider the following example:
```c
int num;
int *pi = 0;    // Zero refers to the null pointer,NULL 
pi = &num;
*pi = 0;        // Zero refers to the integer zero
```
#### Pointer to Void
It has two interesting properties:
* A pointer to void will have the same representation and memory alignmentas a pointer to char.
* A pointer to void will never be equal to another pointer. However, two void pointers assigned a NULL value will be equal.
> Pointers to void are used for data pointers, not function pointers.
The sizeof operator can be used with a pointer to void. However, we cannot use the operator with void as shown below:
```c
size_t size = sizeof(void*); // Legal 
size_t size = sizeof(void); // Illegal
```
#### Global and static pointers
If a pointer is declared as global or static, `it is initialized to NULL when the program starts`.
## Pointer Size and Types
* A pointer to a char has the same size as a pointer to a structure. 
* The size of a pointer to a function may be different from the size of a pointer to data.
* The size of a pointer depends on the machine in use and the compiler.
### Predefined Pointer-Related Types
* `size_t`    : created to provide a safe type for sizes.
* `ptrdiff_t` : Created to handle pointer arithmetic.
* `intptr_t` and `uintptr_t` : Used for storing pointer address.

#### size_t

The declaration of size_t:
```c 
#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned int size_t;
#endif
```

> It is good practice to use size_t when declaring variables for sizes such as the number of characters and array indexes. It should be used for loop counters, indexing into arrays, and sometimes for pointer arithmetic.

#### intptr_t and uintptr_t
They are useful for converting pointers to their integer representation.
> If we try to assign the address of an integer to a pointer of type uintptr_t as follows, we will get a syntax error
```c
int a = 12345;
int *p = &a;
int ptr = (int)p;
```
it'll cause `Wpointer-to-int-cast` warning, because sizeof(int) and sizeof(int pointer) are different.
We need to use `intptr_t` or `uintptr_t` :
```c
uintptr_t a = 12345;
uintptr_t *p = &a;
uintptr_t ptr = (uintptr_t)p;
```
### Multiple Levels of Indirection
Using multiple levels of indirection provides additional flexibility in how code can be written and used. Certain types of operations would otherwise be more difficult.
### Constants and Pointers
We cannot dereference a constant pointer to change what the pointer references, but we can change the pointer.
```c
int num = 10;
const int *ptr1 = &num;         // ptr1 is a pointer variable point to a const int
int *const ptr2 = &num;         // const pointer variable ptr2 point to a int, we cannot modify ptr2
```
Example:
```c
int num = 5;
const int limit = 500; 
int *pi;                // Pointer to an integer
const int *pci;         // Pointer to a constant integer

pi = &num;
pci = &limit;
```
* pci can be assigned to point to different constant integers
* pci can be assigned to point to different nonconstant integers 
* pci can be dereferenced for reading purposes
* pci cannot be dereferenced to change what it points to

### Constant pointers to "nonconstants"
Example:
```c
int num;
int limit = 500;
int *const cpi = &num;
cpi = &limit;
```
The error message:
```shell
'cpi' : you cannot assign to a variable that is const
```
> reference Fig: In textbook p.29 Figure 1-13

### Constant pointers to "constants"
Given a constant pointer to a constant we cannot:
* Modify the pointer
* Modify the data pointed to by the pointer
### Summary
| Pointer                             | Pointer Modifiable | Data Pointed to Modifiable |
|-------------------------------------|---|---|
| Pointer to a `nonconstant`          | Y | Y |
| Pointer to a `constant`             | Y | N |
| Constant pointer to a `nonconstant` | N | Y |
| Constant pointer to a `constant`    | N | N |

