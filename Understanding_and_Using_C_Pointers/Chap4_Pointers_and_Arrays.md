# Chap 4: Pointers and Arrays
```c

// one-dimension array
int vector[5] = {1, 2, 3, 4, 5};

// two-dimension array
int matrix[2][3] = {{1, 2, 3},
                    {4, 5, 6}};

// multi-dimensional array
int arr3d[3][2][4] = {
    {{1, 2, 3, 4}, {5, 6, 7, 8}},
    {{9, 10, 11, 12}, {13, 14, 15, 16}},
    {{17, 18, 19, 20}, {21, 22, 23, 24}}
    };

```

## Pointer Notation and Arrays
Pointers can be very useful when working with arrays. We can use them with existing arrays or to `allocate memory from the heap and then treat the memory as if it were an array`.
> When an array name is used by itself, the array’s address is returned.
```c
int vector[5] = {1, 2, 3, 4, 5};
int *pv = vector;

// They're the same--------
printf("%p\n", vector);
printf("%p\n", vector[0]);
//-------------------------

printf("%d\n", sizeof(vector)); // it will return 20
printf("%d\n", sizeof(pv));     // it will return 4, the pointer's size

pv = pv + 1;
vector = vector + 1; // Systax error, we can't modify vector, only its contents
pv = vector + 1; // it'll be fine

```
## Differences Between Arrays and Pointers
* `vector[i]` and `vector + i` in code generated are diffenent.
> * `vector[i]` generates machine code that starts at location *vector* `moves` *i* positions from this location
> * `vector + i` generates machine code that starts at location *vector* `adds` *i* to the address, then uses the contents at the address.
### Lvalue
* An lvalue denotes the term used on the lefthand side of an assignment operator
* An lvalue must be capable of being modified

> The address assigned to an `array` cannot be changed . 
> A `pointer` can be assigned a new value and reference a different section of memory.

## Using malloc to Create a One-Dimensional Array
```c
int *pv = (int *) malloc(5 * sizeof(int));
for(int i = 0; i < 5; i++) {
    //*(pv + i) = i + 1;
    pv[i] = i + 1;
}
```
## Using realloc Function to Resize an Array

