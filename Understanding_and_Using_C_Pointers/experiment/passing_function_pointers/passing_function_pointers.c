#include <stdio.h>

int add(int num1, int num2) 
{
    return num1 + num2;
}

int sub(int num1, int num2)
{
    return num1 - num2;
}

typedef int (*funcptr_op)(int, int);

int calculate(funcptr_op op, int num1, int num2)
{
    return op(num1, num2);
}

int main()
{
    printf("%d\n", calculate(add, 10, 20));
    printf("%d\n", calculate(sub, 10, 20));
    return 0;
}
