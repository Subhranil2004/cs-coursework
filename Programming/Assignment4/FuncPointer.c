// Display the address of a user-defined function.
#include <stdio.h>
int add(int, int);
int main()
{
    int a, b, sum;
    int (*p_add)(int, int);
    p_add = &add;
    printf("Enter two integers = ");
    scanf("%d%d", &a, &b);
    printf("Address of add() function : %p\twhich returns the value = %d\n", p_add, (*p_add)(a, b)); // &add instead of p_add...
    return 0;
}
int add(int a, int b)
{
    return a + b;
}
