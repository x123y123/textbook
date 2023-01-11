# The order of variables when stack frame is created
When the stack frame is created, the parameters are pushed onto the frame in the opposite order of their declaration, followed by the local variables.
1. ready to call `average()` in main function
    1. push `parameters` to stack memory
    2. then, push `return 0` to stack memory
    3. program counter(PC) set to first instruction in average()
2. execute average()
     
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


