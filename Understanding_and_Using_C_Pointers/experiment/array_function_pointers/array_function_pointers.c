#include <stdio.h>

int add (int n1, int n2)
{
    return n1 + n2;
}

int sub(int n1, int n2)
{
    return n1 - n2;
}

//-------------------------
typedef int (*funcptr_op) (int, int);
funcptr_op operations[128] = {NULL};

// int (*operations[128]) (int, int) = {NULL};
//-------------------------

void init_op_array()
{
    operations['+'] = add;
    operations['-'] = sub;
}

// using the operation character as an index
int evaluate_arr( char opcode, int n1, int n2)
{
    funcptr_op op;
    op = operations[opcode];
    return op(n1, n2);
}

int main()
{
    init_op_array();

    printf("%d\n", evaluate_arr('+', 25, 10));
    printf("%d\n", evaluate_arr('-', 25, 10));

    return 0;
}
