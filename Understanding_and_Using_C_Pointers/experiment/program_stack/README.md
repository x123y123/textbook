# The order of variables when stack frame is created
When the stack frame is created, the parameters are pushed onto the frame in the opposite order of their declaration, followed by the local variables.
## compile with gcc and run the program
```shell
$ gcc program_stack.c 
$ ./a.out
```

## Output
you will get the output similar to the following:
```shell
arr: 0x16dd433a8
size: 0x16dd433a4
sum: 0x16dd433a0
```
## The concept

1. ready to call `average()` in main function
    1. push `parameters` to  stack memory -------- push `&a[0]` and `size` to stack memory
    2. then, push `return 0` to stack memory ----- push address of `return 0`
    3. program counter(PC) set to first instruction in average() 
2. execute average()
    1. push old frame pointer to stack memory
    2. set stack top to frame pointer
    3. move stack pointer and allocate a free memory to store all local variables of average() on stack memory
    4. execute `printf()`
    5. move return value to system variable
    6. set frame pointer value to stack pointer
    7. recover frame pointer to old frame pointer
    8. pop address of `return 0`

