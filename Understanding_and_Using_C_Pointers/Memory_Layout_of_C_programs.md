# Memory Layout of C programs
A typical memory representation of a C program(`running process`) consists of the following sections:
* Text segment (i.e. instructions)
* Initialized data segment : (Ex. int a = 5 or char s[] = "hello" )
    * contain `global` variables and `static` variables
* Uninitialized data segment (bss) : (Ex. static int a )
    * bss : block started by symbol
* Heap 
    * Dynamic memory management
* Stack: 
    * contain the data function used when `Function call` happened 
    * when the stack pointer met the heap pointer, free memory was exhausted.


```html
high address-----> ------------
                  |             |
                   -------------
                  |    stack    |
                   -------------
                  |      |      |
                  |      ˇ      |
                  |             |
                  |             |
                  |      ^      |
                  |      |      |
                   -------------
                  |    heap     |
                   -------------
                  |uninitialized|
                  |  data(bss)  |
                   -------------
                  | initizlized |
                  |     data    |
                   -------------
                  |     text    |
 low address---->  -------------
```

## Referense
[Geeksforgeeks](https://www.geeksforgeeks.org/memory-layout-of-c-program/)
