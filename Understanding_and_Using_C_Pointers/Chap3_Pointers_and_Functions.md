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
