// Write a program to find out maximum of 5 numbers
#include <stdio.h>

int main()
{
    int a, b, c, d, e;

    printf("Enter 5 numbers : ");
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

    if (a > b && a > c && a > d && a > e)
    {
        printf("%d is maximum\n", a);
    }
    else if (b > c && b > d && b > e)
    {
        printf("%d is maximum\n", b);
    }
    else if (c > d && c > e)
    {
        printf("%d is maximum\n", c);
    }
    else if (d > e)
    {
        printf("%d is maximum\n", d);
    }
    else
    {
        printf("%d is maximum\n", e);
    }

    return 0;
}
