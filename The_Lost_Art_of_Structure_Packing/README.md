# The Lost Art of Structure Packing
* One of ways to reduce memory usage: `rearranging the order of structure members`

> * chars can start on any byte address
> * 2-byte shorts must start on an even address
> * 4-byte ints or floats must start on an address divisible by 4
> * 8-byte longs or doubles must start on an address divisible by 8

## Padding
* In 64-bit machine
```c
char *p; // 8 bytes
char c;  // 1 byte
long x;  // 8 bytes
```
we end up with this:
```c
char *p;        // 8 bytes
char c;         // 1 byte
char pad[7];    // 7 bytes
long x;         // 8 bytes
```
* if we let the shorter variable declaration comes first:
```
char c;
char *p;
int x;
```
we may get:
```c
char c;
char pad[7]; // if compiler unlucky not happened to map char c to the last byte of a machine word, it will pad 7 bytes.
char *p;
int x;
```
if we want to make these variables `take up less space`:
```c
char *p;
int x;
char c; // swapping c to the last
```

## Reference
* [ebook](http://www.catb.org/esr/structure-packing/)
