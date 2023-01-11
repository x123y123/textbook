#include <stdio.h>

float average(int *arr, int size) { 
    int sum;
    printf("arr: %p\n",&arr); 
    printf("size: %p\n",&size); 
    printf("sum: %p\n",&sum);
    for(int i=0; i<size; i++) { 
        sum += arr[i];
    }
    return (sum * 1.0f) / size; 
}


int main()
{
    int a[] = {12, 15};
    average(&a[0], 2);
    return 0;
}
