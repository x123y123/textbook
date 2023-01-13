#include <stdio.h>

int add(int n1, int n2)
{
    return n1 + n2;
}

int sub(int n1, int n2)
{
    return n1 - n2;
}

typedef int (*funcptr_op)(int, int);

funcptr_op select(char opcode)
{
    switch(opcode) {
        case '+': return add;
        case '-': return sub;
    }
}

int evaluate(char opcode, int n1, int n2)
{
    funcptr_op op = select(opcode);
    return op(n1, n2);
}

int main()
{
    printf("'+': %d\n", evaluate('+', 5, 6));
    printf("'-': %d\n", evaluate('-', 5, 6));

    return 0;
}
