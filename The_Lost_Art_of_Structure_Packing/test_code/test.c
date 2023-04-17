#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

struct AlignedStruct {
    char c[8];
    int i __attribute__((aligned(16)));
    double d;
};

struct UnalignedStruct {
    char c;
    int i;
    double d;
};

int main() {
    struct AlignedStruct aligned_arr[ARRAY_SIZE];
    struct UnalignedStruct unaligned_arr[ARRAY_SIZE];
    struct timespec start, end;
    double cpu_time_used;

    // initialize the arrays
    for (int i = 0; i < ARRAY_SIZE; i++) {
        aligned_arr[i].c = 'abcefils';
        aligned_arr[i].i = i;
        aligned_arr[i].d = i + 0.5;

        unaligned_arr[i].c = 'a';
        unaligned_arr[i].i = i;
        unaligned_arr[i].d = i + 0.5;
    }


    // access the variables in the unaligned array and time how long it takes
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        unaligned_arr[i].c;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time_used = diff_in_second(start, end);
    printf("Time taken to access char variables in unaligned array: %f seconds\n", cpu_time_used);

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        unaligned_arr[i].i;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time_used = diff_in_second(start, end);
    printf("Time taken to access int variables in unaligned array: %f seconds\n", cpu_time_used);

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        unaligned_arr[i].d;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time_used = diff_in_second(start, end);
    printf("Time taken to access double variables in unaligned array: %f seconds\n", cpu_time_used);

    // access the variables in the aligned array and time how long it takes
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        aligned_arr[i].c;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time_used = diff_in_second(start, end);
    printf("Time taken to access char variables in aligned array: %f seconds\n", cpu_time_used);

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        aligned_arr[i].i;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time_used = diff_in_second(start, end);
    printf("Time taken to access int variables in aligned array: %f seconds\n", cpu_time_used);

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        aligned_arr[i].d;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time_used = diff_in_second(start, end);
    printf("Time taken to access double variables in aligned array: %f seconds\n", cpu_time_used);
    return 0;
}

