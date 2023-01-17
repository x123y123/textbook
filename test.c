#include <stdio.h>

void add(int a, int b) {
    return a + b;
}

int main()
{
    int a = 10;
    int b = 5;
    if (a > b) {
        add(a, b);
    } else
        return 0;
    return 0;
}
