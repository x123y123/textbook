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
## Using the realloc Function to Resize an Array
We can resize an existing array created using malloc with the realloc function. The essentials of the realloc function were detailed in Chapter 2. The C standard C99 supports variable length arrays. In some situations, this may prove to be a better solution than using the realloc function. If you are not using C99, then the realloc function will need to be used. Also, variable length arrays can only be declared as a member of a function. If the array is needed longer than the function’s duration, then realloc will need to be used.

## Passing a One-Dimensional Array
We can declare the array in the function declaration using one of two notations:
* Array notation 
```c
void display_array(int arr[], int size) {// ...};
```
* Pointer notation.
```c
void display_array(int *arr, int size) {// ...};
```
## Using a One-Dimensional Array of Pointers
* (arr + i) represents the address of the array's $i^(th)$ element.

### Example 
```c
int *arr[5];
for (int i = 0; i < 5; i++) {
   
    //method_1
    arr[i] = (int*)malloc(sizeof(int));
    *arr[i] = i;

    //method_2
    *(arr + i) = (int*)malloc(sizeof(int));
    **(arr + i) = i;
}
```
* Array of pointers expressions
|Expression|Value|
|----------|-----|
|`*arr[0]` | 0   |
|`**arr`   |0    |
|`**(arr + 1)`|1 |
|`arr[0][0]`| 0  |
|`arr[3][0]`|3   |

> The expression arr[3][1] does not work because the array the fourth element is pointing to does not have two elements.
#### Two-dimensional array notation
* arr[i][j]
> address of `arr + (i * size of row) + (j * size of element)`

## Dynamically Allocating a Two-Dim Array
Since a two-dimensional array can be treated as an `array of arrays`, there is `no reason the “inner” arrays need to be contiguous`.
> Whether or not it is contiguous can affect other operations, such as copying a block of memory. `Multiple copies may be required if the memory is not contiguous`.
### Allocting Potentially Noncontiguous Memory
```c
int rows = 2;
int cols = 5;

int **matrix = (int**)malloc(rows * sizeof(int*));
for (int i = 0; i < rows; i++) {
    matrix[i] = (int*)malloc(cols * sizeof(int);
}
```
> The actual allocation depends on the heap manager and the heap’s state. It may well be contiguous.

### Allocating Contigous Memory
There are two approaches for allocating coniguous memory for 2D array:
* Allocates the `outer` array first, then all of memory for the rows.
```c
int rows = 2;
int cols = 5;

int **matrix = (int **) malloc(rows * sizeof(int *));
//malloc all elements for the rows
matrix[0] = (int *) malloc(rows * cols * sizeof(int));
for (int i = 0; i < rows; i++) {
    matrix[i] = matrix[0] + i * cols;
}
```
* Allocates all of memory at once.
```c
int *matrix = (int *) malloc(rows * cols * sizeof(int));
```
> When the array is referenced later in code, array subscripts cannot be used. Instead, indexes into the array need to be calculated manually
>> Array subscripts cannot be used because we have lost the shape information needed by the compiler to permit subscripts.

## Jagged Array and Pointers
* `compound literal`
```c
// compound literal declare like this
(const int) {100}
(int[3]) {10, 20, 30}

// we can use like this in 2D array
int (*(arr1[])) = {
    (int[]) {0, 1, 2},
    (int[]) {3, 4, 5},
    (int[]) {6, 7, 8}
};

// then we can try to use compound literal to create the jagged array
int (*(arr1[])) = {
    (int[]) {0, 1, 2, 3},
    (int[]) {4, 5},
    (int[]) {6, 7, 8}
};
```

