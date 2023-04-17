# Memory Alignment Test
Device: Macbook M1 Air
## How to use?
* drop cache
```shell
$ sudo purge
```
* Compile and run
```shell
$ gcc -O0 test.c 
$ ./a.out
```
## Result
```shell
Time taken to access char variables in unaligned array: 0.000451 seconds
Time taken to access int variables in unaligned array: 0.000249 seconds
Time taken to access double variables in unaligned array: 0.000331 seconds
Time taken to access char variables in aligned array: 0.000310 seconds
Time taken to access int variables in aligned array: 0.000300 seconds
Time taken to access double variables in aligned array: 0.000201 seconds
```
> It is more likely that the difference in performance is due to caching effects.
## Summary
We may need to test in more diffenent compiler or OS.
The differences in timing between the two types of access are quite small, on the order of microseconds. 
It's possible that the differences are due to other factors, such as cache effects or measurement noise.

