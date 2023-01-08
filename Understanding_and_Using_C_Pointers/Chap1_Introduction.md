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
```clike
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
```clike
const int *pci;
```
1. pci is a variable                                               `pci;`
2. pci is a pointer variable                                      `*pci;`
3. pci is a pointer variable to an integer                    `int *pci;`
4. pci is a pointer variable to a constant integer      `const int *pci;`

## Address of operator - "&"
> Assignment of integers to a pointer will generally cause a warning or error.

But if we cast an integer to a pointer to an integer:
```clike 
pi = (int *)num;
```
This will not generate a syntax error. When executed, though, the program may `terminate abnormally` when the program attempts to dereference the value `at address zero`.

## Displaying pointer values

```clike
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
```clike
int num = 5;
int *pi = &num;
printf("%p\n", *pi);  // Display 5
```
## Pointer to Functions
```clike
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
```clike
#define NULL    ((void *)0)

// this define can be found in stddef.h, stdlib.h, stdio.h
```
The use of NULL and 0 are language-level symbols that represent a null pointer.

> A null pointer and an uninitialized pointer are different. An uninitial‐ ized pointer can contain any value, whereas a pointer containing NULL does not reference any location in memory.
```clike
// pi is a pointer variable
pi = 0;
pi = NULL;
pi = 100;   // Syntax error
pi = num;   // Syntax error
//Interestingly, we can assign a zero to a pointer, but we cannot assign any other integer value. 
```
> A null pointer should never be dereferenced because it does not contain a valid address. When executed it will result in the program terminating.

```
