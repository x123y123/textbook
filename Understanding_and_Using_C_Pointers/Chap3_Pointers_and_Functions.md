# Chap 3: Pointers and Functions
## Program Stack and Heap
* `Stack` frames hold the parameters and local variables `of a function`. 
* The `heap` manages `dynamic memory`.
### Program Stack
* The program stack is an area of memory that supports the execution of functions and is normally shared with the heap.
* The program stack holds stack frames, sometimes called activation records or activation frames.

#### Organization of a Stack Frame
A stack frame consists of several elements, including:
* Return address
* Storage for local data
* Storage forr parameters
* Stack and base pointers
> * Each thread is typically allocated its own program stack, as stack frames are pushed onto the program stack, the system may run out of memory. This condition is called `stack overflow`.
> * When the stack pointer met the heap pointer, free memory was exhausted. => `stack overflow`.

#### Based Pointer v.s. Stack Pointer
* The stack pointer always points to the top (or bottom, if you prefer) of the stack.
* The frame pointer always points to the frame.
#### Returning a Pointer
```c
int* allocateArray(int size, int value) {
    int* arr = (int*)malloc(size * sizeof(int)); 
    for(int i=0; i<size; i++) {
            arr[i] = value;
    }
    return arr; 
}

/* While the arr variable went away when the function terminated, the memory referenced by the pointer does not go away. This memory will eventually need to be freed. */

int main()
{
    int* vector = allocateArray(5,45); 
    for(int i=0; i<5; i++) 
        printf("%d\n", vector[i]); 

    free(vector);        // We must eventually free vector once we are through using it. If we don’t, then we will have a memory leak.

    return 0;
}
```
#### Pointers to Local Data

```c
int* allocateArray(int size, int value) {
    
    int arr[size];  // local array

    for(int i=0; i<size; i++) {
            arr[i] = value;
    }
    return arr; 
}

/* the address of the array returned is no longer valid once the function returns because the function’s stack frame is popped off the stack. */

int main()
{
    int* vector = allocateArray(5,45); 

    for(int i=0; i<5; i++) 
        printf("%d\n", vector[i]);  // the printf function is invoked repeatedly, resulting in corruption of the array    

    return 0;
}
```
> We can declare the `arr` variable as `static`. This will restrict the variable's scope to the function but allocate it outside of the stack frame, eliminating the possibility of another function overwriting the variable’s value.

static declare:
```c
int* allocateArray(int size, itn value) {
    static int arr[5];
    //...
}
```
> In addition, the static array must be declared with a fixed size. This will limit the function’s ability to handle various array sizes.
#### Pasing NULL Pointers
When a pointer is passed to a function, it is always good practice to verify it is not null before using it.
```c
int* allocateArray(int *arr, int size, int value) {
    if(arr != NULL) {
    // ...
    }
    return arr;
}
```
> If the pointer is NULL, then no action is performed and the `program will execute without terminating abnormally`.
#### Passing a Pointer to a pointer
When a pointer is passed to a function, it is passed by value. If we want to modify the original pointer and not the copy of the pointer, we need to pass it as a pointer to a pointer.
```c
void allocateArray(int **arr, int size, int value) { 
    *arr = (int*)malloc(size * sizeof(int));
    if(*arr != NULL) {
        for(int i=0; i<size; i++) { 
            *(*arr+i) = value;
        } 
    }
}

int main()
{
    int *vector = NULL; 
    allocateArray(&vector,5,45);
}
```
### Function pointers
One concern regarding the use of function pointers is a potentially slower running program. The processor may not be able to use `branch prediction` in conjunction with pipelining. 
> Branch prediction is a technique whereby the processor will guess which multiple execution sequences will be executed. Pipelining is a hardware technology commonly used to improve processor performance and is achieved by overlapping instruction execution. In this scheme, the processor will start processing the branch it believes will be executed. If the processor successfully predicts the correct branch, then the instructions currently in the pipeline will not have to be discarded.
* Function pointer declaration
```c
int (*f1)(double);          // passed a double and returns an int

void (*f2)(char*);          // Passed a pointer to char and returns void

double* (*f3)(int ,int);    // Passed two integers and returns a pointer to a double
```
> naming convention for function pointers is to always begin their name with the prefix: `fptr`.
```c
int *f4();      // a function that returns a pointer to an integer

int (*f5)();    // a function pointer that pointer returns an integer

int* (*f6)();   // a function pointer that returns a pointer to an integer
```

#### Using a Function Pointer
```c
int (*fptr1)(int);
int square(int num) 
{
    return num * num;
}

int main()
{
    int n = 5;
    fptr1 = square;     // As with array names, when we use the name of a function by itself, it returns the function’s address.
    printf("%d squared is %d\n", n, fptr1(n));

    return 0;
}
```
We could have used like following:
```c
fptr1 = &square;
```
but it is not necessary and is `redundant`. The compiler will effectively ignore the address-of operator when used in this context.
* Normally, it is convenient to declare a type definition for function pointers.
```c
typedef int (*funcptr)(int);
// ...
funcptr fptr1;
fptr1 = square;
```
#### Casting Function Pointers
* A pointer to one function can be cast to another type. (carefully, since the runtime system does not verify that parameters used by a function pointer are correct) 
